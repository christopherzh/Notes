//给出一个磁盘块序列：1、2、3、……、500，初始状态所有块为空的，每块的大小为2k。选择使用空闲表来管理空闲块。对于基于块的索引分配执行以下步骤：
//（1）	随机生成2k-10k的文件50个，文件名为1.txt、2.txt、……、50.txt，按照上述算法存储到模拟磁盘中。
//（2）	删除奇数.txt（1.txt、3.txt、……、49.txt）文件
//（3）	新创建5个文件（A.txt、B.txt、C.txt、D.txt、E.txt），大小为：7k、5k、2k、9k、3.5k，按照与（1）相同的算法存储到模拟磁盘中
//（4）	给出文件A.txt、B.txt、C.txt、D.txt、E.txt的盘块存储状态和所有空闲区块的状态。
class Table { //空闲块表
    constructor(num, blockAddr, blockSize) {
        this.num = num
        this.blockAddr = blockAddr
        this.blockSize = blockSize
    }
}

class FCB { //文件控制表
    constructor(name, inode) {
        this.name = name
        this.imode = inode
    }
}

var MaxBlockNum = 500    //磁盘块号
var MaxBlockSize=2
var FCBTable = new Array()  //文件目录，二维
var IndexNodeTable = new Array(60) //索引结点表
var FreeTable = new Array()   //空闲分区表，二维
FreeTable[0] = new Table(1, 1, MaxBlockNum)

function createFile(requestSize,fileName) {
    var t=FCBTable.length
    FCBTable[t]=new FCB(fileName,t) //创建FCB
    IndexNodeTable[t]=new Array() //创建inode
    var needBlockNum=Math.ceil(requestSize/MaxBlockSize) 
    var posInFreeTable=0
    //进行分配
    while(needBlockNum>0){
        if(posInFreeTable<=FreeTable.length){
            while(FreeTable[posInFreeTable].blockSize>0){
                FreeTable[posInFreeTable].blockSize--
                needBlockNum--
                IndexNodeTable[t].[IndexNodeTable[t].length]=FreeTable[posInFreeTable].blockAddr
                FreeTable[posInFreeTable].blockAddr++

            }
            FreeTable.splice(posInFreeTable, 1)
            posInFreeTable++
        }
        else{
            alert('空间不足，无法分配！')
        }
    }
}

function deleteFile(fileName) {

}

function stepOne() {
    for(var i=0;i<50;i++){
        var size=Math.floor(2 + Math.random() * 8)
        createFile(size,(i+1)+'.txt')
    }
}

function stepTwo() {
    for(var i=0;i<50;i+=2){
        deleteFile((i+1)+'.txt')
    }
}

function stepThree() {
    var FileNameList=['A','B','C','D','E']
    var FileSizeList=[7,5,2,9,3.5]
    for(var i=0;i<FileNameList.length;i++){
        createFile(FileSizeList[i],FileNameList[i]+'.txt')
    }
}

function stepFour() {

}