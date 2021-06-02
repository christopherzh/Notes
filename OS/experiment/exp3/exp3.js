var requestList = [55, 58, 39, 18, 90, 160, 150, 38, 184];
var moveLength = new Array(10);
for (var i = 0; i < 10; i++) {
    moveLength[i] = 10000;
}
var nowPos = 100;
function SCAN() {

}
function SSTF() {
    var i;
    var minPos;
    var nowPos;
    var len = requestList.length;
    for (i = 0; i < len; i++) {
        for (var j = 0; j < requestList.length; j++) {
            if (Math.abs(nowPos - requestList[j]) < moveLength[i]) {
                moveLength[i] = Math.abs(nowPos - requestList[i])
                minPos = requestList[i]; //当前磁头应移到的位置
            }
        }
        nowPos = minPos; //修改当前磁头位置
        document.write(nowPos, '\n');
    }
}
SSTF();