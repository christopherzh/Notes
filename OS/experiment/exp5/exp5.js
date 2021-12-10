//给出一个磁盘块序列：1、2、3、……、500，初始状态所有块为空的，每块的大小为2k。选择使用空闲表来管理空闲块。对于基于块的索引分配执行以下步骤：
//（1）	随机生成2k-10k的文件50个，文件名为1.txt、2.txt、……、50.txt，按照上述算法存储到模拟磁盘中。
//（2）	删除奇数.txt（1.txt、3.txt、……、49.txt）文件
//（3）	新创建5个文件（A.txt、B.txt、C.txt、D.txt、E.txt），大小为：7k、5k、2k、9k、3.5k，按照与（1）相同的算法存储到模拟磁盘中
//（4）	给出文件A.txt、B.txt、C.txt、D.txt、E.txt的盘块存储状态和所有空闲区块的状态。

class Table { //
    constructor(beginAddr, len, sign) {
        this.beginAddr = beginAddr
        this.len = len
        this.sign = sign
    }
}

var MAX = 500    //内存容量,单位KB
var AllocTable = new Array()  //已分区表，二维
var FreeTable = new Array()   //空闲分区表，二维
FreeTable[0] = new Table(1, MAX, 'Null')
var FileNameList = ['A', 'B', 'C', 'D', 'E']
var FileSizeList = [7, 5, 2, 9, 3.5]

function Compare(property) { //首先按照主键升序排序，若相同则按次键升序排列
    return function (obj1, obj2) {
        return obj1[property] - obj2[property]
    }
}


function changeFreeTable(fileName, request, pos) {
    var tempAddr
    if (FreeTable[pos].len > request) { //空闲盘块长度大于请求
        FreeTable[pos].len -= request //修改空闲盘块剩余长度
        tempAddr = FreeTable[pos].beginAddr //保存修改前的地址
        FreeTable[pos].beginAddr += request //修改该区始址
    }
    else { //空闲盘块等于请求
        tempAddr = FreeTable[pos].beginAddr //保存修改前的地址
        FreeTable.splice(pos, 1); //直接删除空闲分区
    }

    AllocTable[AllocTable.length] = new Table(tempAddr, request, fileName)
    AllocTable.sort(Compare('beginAddr')) //将已分配表按始址排序，便于查看
    //alert("文件创建成功")
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
        for (i = 0; i < FreeTable.length; i++) { //直接寻找应插入的位置
            var i
            if (FreeTable[i].beginAddr > begin) {
                break
            }
        }
        FreeTable.splice(i, 0, new Table(begin, end - begin, -1))
    }
    //alert("已释放文件占用的空间")
}

function createFile(request, fileName) {
    for (var i = 0; i < FreeTable.length; i++) {
        if (FreeTable[i].len >= request && FreeTable[i].sign == 'Null') { //找到空闲分区
            changeFreeTable(fileName, request, i)
            return FreeTable[i].beginAddr
        }
    }
    return -1
}

function deleteFile(fileName) {    //块回收算法  
    for (var i = 0; i < AllocTable.length; i++) { //找到应删去的文件，处理已分配表
        if (AllocTable[i].sign == fileName) {
            // 保存删除的空闲区块
            var begin = AllocTable[i].beginAddr
            var end = AllocTable[i].beginAddr + AllocTable[i].len
            AllocTable.splice(i, 1) //从已分配表中删除该项
            searchUpDown_ChangeFreeTable(begin, end) //根据规则修改空闲盘块表
            return 1
        }
    }
    //alert("不存在该文件!")
    return -1
}


function addFreeTable(label, table) {
    var tableData = new String();
    for (var i = 0; i < table.length; i++) {
        var num = i + 1
        tableData += "<tr>"
        tableData += "<td>" + num + "</td>"
        tableData += "<td>" + table[i].beginAddr + "</td>"
        tableData += "<td>" + table[i].len + "</td>"
        tableData += "</tr>"
    }
    $(label).html(tableData)
}

function addTable(label, table) {
    var tableData = new String();
        for (var j = 0; j < table.length; j++) {
                tableData += "<tr>"
                tableData += "<td>" + table[j].sign + "</td>"
                tableData += "<td>" + table[j].beginAddr + "</td>"
                tableData += "<td>" + table[j].len + "</td>"
                tableData += "</tr>"
            
        }
    
    $(label).html(tableData)
}

function draw() { //给出已分配表与未分配表
    addTable("#tbodyAlloc", AllocTable)
    addFreeTable("#tbodyFree", FreeTable)
}

function stepOne() { //第一步
    for (var i = 0; i < 50; i++) {
        var size = Math.floor(2 + Math.random() * 8)
        var blocksize=Math.ceil(size/2)
        var beginAddr = createFile(blocksize, (i + 1) + '.txt')
        if (beginAddr == -1) {
            //alert('建立文件失败，无可用存储块！')
            break
        }
    }
    draw()
    //alert('done')
}

function stepTwo() { //第二步
    for (var i = 0; i < 50; i += 2) {
        deleteFile((i + 1) + '.txt')
    }
    draw()
    //alert('done')
}

function stepThree() { //第三步
    for (var i = 0; i < FileNameList.length; i++) {
        var blocksize=Math.ceil( FileSizeList[i]/2)
        createFile(blocksize, FileNameList[i] + '.txt')
    }
    draw()
    //alert('done')
}

function stepFour() { //第四步
    draw()
    //alert('done')
}

function runAll() { //全部运行
    stepOne()
    stepTwo()
    stepThree()
    stepFour()
    alert('执行完毕!')
}