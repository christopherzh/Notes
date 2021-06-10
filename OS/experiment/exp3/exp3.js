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

function ascCompare(property) {
  return function (obj1, obj2) {
    return obj1[property] - obj2[property];
  }
}

function descCompare(property) {
  return function (obj1, obj2) {
    return obj2[property] - obj1[property];
  }
}

function changeFreeTable() {
  var tempAddr
  if (FreeTable[i].len > request) { //空闲分区长度大于请求
    FreeTable[i].len -= request //修改空闲分区剩余长度
    tempAddr = FreeTable[i].beginAddr //保存修改前的地址
    FreeTable[i].beginAddr += request //修改该区始址
  }
  else { //空闲分区等于请求
    tempAddr = FreeTable[i].beginAddr //保存修改前的地址
    FreeTable.splice(i, 1); //直接删除空闲分区
  }
  AllocTable[AllocTable.length] = new Table(tempAddr, request, id)
}

function firstFit(id, request) {
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable()
      return FreeTable[i].beginAddr
    }
  }
  return -1
}

function nextFit(id, request) {
  for (var i = NowPoint, j = 0; j < FreeTable.length; i = (i + 1) % FreeTable.length, j++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable()
      NowPoint = (NowPoint + j) % FreeTable.length
      return FreeTable[i].beginAddr
    }
  }
  return -1

}
function bestFit(id, request) {
  FreeTable.sort(ascCompare(len))
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable()
      return FreeTable[i].beginAddr
    }
  }
  return -1
}


function worstFit(id, request) {
  FreeTable.sort(descCompare(len))
  for (var i = 0; i < FreeTable.length; i++) {
    if (FreeTable[i].len >= request && FreeTable[i].sign == -1) { //找到空闲分区
      changeFreeTable()
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


function retrieve(id) {    //内存回收算法
  var up = -1, down = -1, begin, end //指示是否存在上下分区
  for (var i = 0; i < AllocTable.length; i++) {
    if (AllocTable[i].sign == id) {
      // 保存删除的空闲分区
      begin = AllocTable[i].beginAddr
      end = AllocTable[i].beginAddr + AllocTable[i].len
      AllocTable.splice(i, 1) //从已分配表中删除该项
      break
    }
  }
  for (var j = 0; j < FreeTable.length; j++) {
    if (FreeTable[j].beginAddr + FreeTable[j].len == begin) {
      up = j
    }
    else if (end == FreeTable[j].beginAddr) {
      down = j
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
    FreeTable.splice(FreeTable.length, 0, new Table(begin, end - begin, -1)) //为方便，直接在表最后插入该项
    if (Choice == 0 || Choice == 1) {
      FreeTable.sort(ascCompare(beginAddr)) //如果算法为首次和循环首次适应，则应该重新排序，因为新加入了一个未知表项
    }

  }

  //若分配算法为最佳或最坏适应算法，应重新进行排序
  if (Choice == 2) {
    FreeTable.sort(ascCompare(len))
  }
  else if (Choice == 3) {
    FreeTable.sort(descCompare(len))
  }

  draw()
}


function addTable(label, table) {
  var tableData = new String();
  for (var i = 0; i < table.length; i++) {
    tableData += "<tr>"
    tableData += "<td>" + table[i].beginAddr + "</td>"
    tableData += "<td>" + table[i].len + "</td>"
    if (label == "#tbodyFree") {
      tableData += "<td>J" + table[i].sign + "</td>"
    }
    tableData += "<td>" + table[i].sign + "</td>"
    tableData += "</tr>"
  }
  $(label).html(tableData)
}

function draw() { //给出已分配表与未分配表
  addTable("#tbodyFree", FreeTable)
  AllocTable.sort(ascCompare(beginAddr)) //将已分配表按始址排序，便于查看
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

//Choice=getChoice()
