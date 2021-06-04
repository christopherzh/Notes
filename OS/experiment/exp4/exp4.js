var LEN = 9;
var requestList = new Array(LEN);
var moveLength = new Array(LEN);
var nowPos;
var startPos;
var startList = new Array(LEN);
var moveList = new Array(LEN + 1);
function randomGen() {
  startPos = Math.floor(150 + Math.random() * 25);
  for (var i = 0; i < startList.length; i++) {
    startList[i] = Math.floor(Math.random() * 300);
  }
}
function init() {
  nowPos = startPos;
  for (var i = 0; i < startList.length; i++) {
    requestList[i] = startList[i];
  }
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
      if (requestList[j] >= nowPos && requestList[j] - nowPos < moveLength[i]) {
        moveLength[i] = requestList[j] - nowPos;
        minPos = j; //当前磁头应移到的位置
      }
    }
    if (minPos == nowPos) { //右侧没有任何要读的了
      for (var j = 0; j < requestList.length; j++) {
        if (requestList[j] <= nowPos && nowPos - requestList[j] < moveLength[i]) {
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
  moveList[LEN] = nowPos;
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


function draw() {

    var pt1 = new Array(LEN + 1);
    var pt2 = new Array(LEN + 1);

    randomGen();
    init();
    SSTF();
    for (var i = 0; i < pt1.length; i++) {
      pt1[i] = { x: i + 1, y: moveList[i] }
    }
    var chart1 = new CanvasJS.Chart("SSTFchartContainer",
      {
        animationEnabled: true,
        animationDuration: 5000,
        exportEnabled: true,
        title: {
          text: "SSTF磁盘移臂调度算法"
        },
        data: [
          {
            type: "line",
            indexLabel: "{y}",
            dataPoints: pt1
          }
        ]
      });
    chart1.render();
    addTable("#tbody1");
    init();
    SCAN();
    for (var i = 0; i < pt1.length; i++) {
      pt2[i] = { x: i + 1, y: moveList[i] }
    }
    var chart2 = new CanvasJS.Chart("SCANchartContainer",
      {
        animationEnabled: true,
        animationDuration: 5000,
        exportEnabled: true,
        title: {
          text: "SCAN磁盘移臂调度算法"
        },
        data: [
          {
            type: "line",
            indexLabel: "{y}",
            dataPoints: pt2
          }
        ]
      });
    chart2.render();

    addTable("#tbody2");
    
    var tableData = new String();
    tableData += "<tr><th>起始</th>"
    for (var i = 0; i < startList.length; i++) {
      tableData += "<th>" + (i + 1) + "</th>"
    }
    tableData += "</tr>"
    $("#thead").html(tableData)

    tableData = new String();
    tableData += "<tr>" + "<td>" + startPos + "</td>"
    for (var i = 0; i < startList.length; i++) {
      tableData += "<td>" + startList[i] + "</td>"
    }
    tableData += "</tr>"
    $("#tbody").html(tableData)



  }
window.onload = function () {
draw()
}