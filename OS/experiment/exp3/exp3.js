var MAX = 1000    //内存容量,单位KB
var AllocTable = new Array()  //已分区表，二维
var FreeTable = new Array()   //空闲分区表，二维
var NowPoint=0 //用于nextFit算法，指明当前头指针
function firstFit(){

}
function nextFit(){ 

}
function bestFit(){

}
function worstFit(){

}
function allocate(id,request) {    //内存分配算法
    //寻找空闲分区
    //空闲分区表的修改
    //已分区表的修改
}
function retrieve(id) {    //内存回收算法
    //若回收的分区有上邻空闲分区和下邻空闲分区
    //要求合并为一个空闲分区登记在空闲分区表的一个表项里。
}

function addTable(label) {
    var tableData = new String();
    var sum = 0;
    for (var i = 0; i < moveLength.length; i++) {
      sum += moveLength[i];
    }
    for (var i = 0; i < moveLength.length; i++) {
      tableData += "<tr>"
      tableData += "<td>" + moveList[i + 1] + "</td>"
      tableData += "<td>" + moveLength[i] + "</td>"
      tableData += "</tr>"
      //现在tableData已经生成好了，把他赋值给上面的tbody
    }
    tableData += "<tr>"
    tableData += "<td>移臂总量</td>"
    tableData += "<td>" + sum + "</td>"
    tableData += "</tr>"
    $(label).html(tableData)
  }

function draw() { //给出已分配表与未分配表
    
}
function test(){
    var a = document.getElementById("info").value;
    alert(a);
}
