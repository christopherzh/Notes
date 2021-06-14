class Table {
  constructor(beginAddr, len, sign) {
    this.beginAddr = beginAddr
    this.len = len
    this.sign = sign
  }
}

var MAX = 1000    //内存容量,单位KB
var AllocTable = new Array()  //已分区表，二维
var FreeTable = new Array()   //空闲分区表，二维
FreeTable[0] = new Table(0, MAX, -1)
var NowPoint = 0 //用于nextFit算法，指明当前头指针
var Choice = 0 //算法选择

function ascCompare(property1, property2) { //首先按照主键升序排序，若相同则按次键升序排列
  return function (obj1, obj2) {
    var temp = obj1[property1] - obj2[property1]
    if (temp != 0)
      return temp
    else
      return obj1[property2] - obj2[property2]
  }
}

function descCompare(property1, property2) { //首先按照主键降序排序，若相同则按次键升序排列
  return function (obj1, obj2) {
    var temp = obj2[property1] - obj1[property1]
    if (temp != 0)
      return temp
    else
      return obj1[property2] - obj2[property2]
  }
}

function changeFreeTable(id, request, pos) {
  var tempAddr
  if (FreeTable[pos].len > request) { //空闲分区长度大于请求
    FreeTable[pos].len -= request //修改空闲分区剩余长度
    tempAddr = FreeTable[pos].beginAddr //保存修改前的地址
    FreeTable[pos].beginAddr += request //修改该区始址
  }
  else { //空闲分区等于请求
    tempAddr = FreeTable[pos].beginAddr //保存修改前的地址
    FreeTable.splice(pos, 1); //直接删除空闲分区
  }

  AllocTable[AllocTable.length] = new Table(tempAddr, request, id)
  AllocTable.sort(ascCompare('beginAddr','beginAddr')) //将已分配表按始址排序，便于查看
  alert("分配内存成功")
}

function firstFit(id, request) {
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable(id, request, i)
      return FreeTable[i].beginAddr
    }
  }
  return -1
}

function nextFit(id, request) {
  for (var i = NowPoint, j = 0; j < FreeTable.length; i = (i + 1) % FreeTable.length, j++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable(id, request, i)
      alert(j)
      NowPoint = (NowPoint + j+1) % FreeTable.length
      alert(NowPoint)
      return FreeTable[i].beginAddr
    }
  }
  return -1

}
function bestFit(id, request) {
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable(id, request, i)
      FreeTable.sort(ascCompare('len','beginAddr'))
      return FreeTable[i].beginAddr
    }
  }
  return -1
}


function worstFit(id, request) {
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable(id, request, i)
      FreeTable.sort(descCompare('len','beginAddr'))
      return FreeTable[i].beginAddr
    }
  }
  return -1
}


function allocate(id, request) {    //内存分配算法
  var beginAddr
  if (Choice == 0) {
    beginAddr = firstFit(id, request)
  }
  else if (Choice == 1) {
    beginAddr = nextFit(id, request)
  }
  else if (Choice == 2) {
    beginAddr = bestFit(id, request)
  }
  else {
    beginAddr = worstFit(id, request)
  }
  if (beginAddr == -1) {
    alert('分配失败，无可用空间！')
  }
  draw()
}

function searchUpDown_ChangeFreeTable(begin, end) {
  var up = -1, down = -1 //指示是否存在上下分区
  for (var i = 0; i < FreeTable.length; i++) { //寻找上下临近区
    if (FreeTable[i].beginAddr + FreeTable[i].len == begin) {
      up = i
    }
    else if (end == FreeTable[i].beginAddr) {
      down = i
    }
  }

  if (up != -1 && down != -1) { //有上下空闲区，修改上空闲项长度，并删去下空闲表
    FreeTable[up].len += (end - begin) + FreeTable[down].len
    FreeTable.splice(down, 1)
  }
  else if (up != -1) { //有上空闲区，修改空闲项长度
    FreeTable[up].len += (end - begin)
  }
  else if (down != -1) { //有下空闲区，修改空闲项始址与长度
    FreeTable[down].len += (end - begin)
    FreeTable[down].beginAddr = begin
  }
  else {  //无上下临近区，向空闲表插入该项

    if (Choice == 0 || Choice == 1) { //若分配算法为首次适应或循环首次适应，则直接寻找应插入的位置
      var i
      for (i = 0; i < FreeTable.length; i++) {
        if (FreeTable[i].beginAddr > begin) {
          break
        }
      }
      FreeTable.splice(i, 0, new Table(begin, end - begin, -1))
    }
    else { //若为最佳分配或最坏分配，则插入到空闲表最后，等待后续重新排序
      FreeTable.splice(FreeTable.length, 0, new Table(begin, end - begin, -1)) //为方便，直接在表最后插入该项
    }
  }

  //若分配算法为最佳或最坏适应算法，应重新进行排序
  if (Choice == 2) {
    FreeTable.sort(ascCompare('len','beginAddr'))
  }
  else if (Choice == 3) {
    FreeTable.sort(descCompare('len','beginAddr'))
  }
  alert("已释放")
  draw()
}

function retrieve(id) {    //内存回收算法  
  for (var i = 0; i < AllocTable.length; i++) { //找到应删去的作业，处理已分配表
    if (AllocTable[i].sign == id) {
      // 保存删除的空闲分区
      var begin = AllocTable[i].beginAddr
      var end = AllocTable[i].beginAddr + AllocTable[i].len
      AllocTable.splice(i, 1) //从已分配表中删除该项
      searchUpDown_ChangeFreeTable(begin, end) //根据规则修改空闲分区表
      return 1
    }
  }
  alert("不存在该作业！")
  return -1
}


function addTable(label, table) {
  var tableData = new String();
  for (var i = 0; i < table.length; i++) {
    tableData += "<tr>"
    tableData += "<td>" + table[i].beginAddr + "</td>"
    tableData += "<td>" + table[i].len + "</td>"
    if (label == "#tbodyFree") {
      tableData += "<td>" + table[i].sign + "</td>"
    }
    else {
      tableData += "<td>J" + table[i].sign + "</td>"
    }
    tableData += "</tr>"
  }
  $(label).html(tableData)
}

function draw() { //给出已分配表与未分配表
  addTable("#tbodyFree", FreeTable)
  addTable("#tbodyAlloc", AllocTable)
}

function getRequest() { //接收用户的请求，并分配空间
  var pid = parseInt(document.getElementById("pid").value)
  var request = parseInt(document.getElementById("request").value)
  allocate(pid, request)
}

function getFree() { //接收用户的释放请求，并释放空间
  var freePid = parseInt(document.getElementById("freepid").value)
  retrieve(freePid)
}

function getChoice() {
  var url = location.search; //这一条语句获取了包括问号开始到参数的最后，不包括前面的路径
  var params = url.substr(1);//去掉问号
  return params
}

Choice = getChoice()
draw()
