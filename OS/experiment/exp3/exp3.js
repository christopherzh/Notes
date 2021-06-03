var LEN = 9;
var requestList = new Array(LEN);
var moveLength = new Array(LEN);
var nowPos;
var startPos;
var startList =new Array(LEN);
var moveList = new Array(LEN + 1);
function randomGen(){
  startPos=Math.floor(50+Math.random()*150);
  for(var i;i<startList.length;i++){
    startList[i]=Math.floor(Math.random()*300);
  }
}
function init() {
  nowPos = startPos;
  requestList = startList;
  moveList = new Array(10);
  for (var i = 0; i < moveLength.length; i++) {
    moveLength[i] = 10000;
  }
}
function SCAN() {
  //var direction=1; //1代表向右，0代表向左
  var len = requestList.length;
  for (var i = 0; i < len; i++) {
    var minPos = nowPos;
    for (var j = 0; j < requestList.length; j++) {
      if (requestList[j] > nowPos && requestList[j] - nowPos < moveLength[i]) {
        moveLength[i] = requestList[j] - nowPos;
        minPos = j; //当前磁头应移到的位置
      }
    }
    if (minPos == nowPos) { //右侧没有任何要读的了
      for (var j = 0; j < requestList.length; j++) {
        if (requestList[j] < nowPos && nowPos - requestList[j] < moveLength[i]) {
          moveLength[i] = nowPos - requestList[j];
          minPos = j; //当前磁头应移到的位置
        }
      }
    }
    moveList[i] = nowPos;
    nowPos = requestList[minPos]; //修改当前磁头位置

    requestList.splice(minPos, 1);
  }
  moveList[9] = nowPos;

}
function SSTF() {

  var len = requestList.length;
  for (var i = 0; i < len; i++) {
    var minPos = nowPos;
    for (var j = 0; j < requestList.length; j++) {
      if (Math.abs(nowPos - requestList[j]) < moveLength[i]) {
        moveLength[i] = Math.abs(nowPos - requestList[j])
        minPos = j; //当前磁头应移到的位置
      }
    }
    moveList[i] = nowPos;
    nowPos = requestList[minPos]; //修改当前磁头位置
    requestList.splice(minPos, 1);
  }
  moveList[9] = nowPos;



}

var pt1;
var pt2;

  randomGen();
  init();
  SSTF();
  pt1 = [
    { x: 1, y: moveList[0] },
    { x: 2, y: moveList[1] },
    { x: 3, y: moveList[2] },
    { x: 4, y: moveList[3] },
    { x: 5, y: moveList[4] },
    { x: 6, y: moveList[5] },
    { x: 7, y: moveList[6] },
    { x: 8, y: moveList[7] },
    { x: 9, y: moveList[8] },
    { x: 10, y: moveList[9] }
  ];
  var chart1 = new CanvasJS.Chart("SSTFchartContainer",
    {
      animationEnabled: true,
      animationDuration: 5000,
      title: {
        text: "SSTF"
      },
      data: [
        {
          type: "line",

          dataPoints: pt1
        }
      ]
    });
  chart1.render();

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
    tableData += "<td>" +sum + "</td>"
    tableData += "</tr>"
  $("#tbody1").html(tableData)


  init();
  SCAN();
  pt2 = [
    { x: 1, y: moveList[0] },
    { x: 2, y: moveList[1] },
    { x: 3, y: moveList[2] },
    { x: 4, y: moveList[3] },
    { x: 5, y: moveList[4] },
    { x: 6, y: moveList[5] },
    { x: 7, y: moveList[6] },
    { x: 8, y: moveList[7] },
    { x: 9, y: moveList[8] },
    { x: 10, y: moveList[9] }
  ];
  var chart2 = new CanvasJS.Chart("SCANchartContainer",
    {
      animationEnabled: true,
      animationDuration: 5000,
      title: {
        text: "SCAN"
      },
      data: [
        {
          type: "line",

          dataPoints: pt2
        }
      ]
    });
  chart2.render();


  tableData = new String();
  sum = 0;
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
    tableData += "<td>" +sum + "</td>"
    tableData += "</tr>"
  $("#tbody2").html(tableData)




