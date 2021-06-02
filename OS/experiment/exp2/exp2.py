import tkinter as tk
import tkinter.messagebox as messagebox
from tkinter.ttk import Progressbar
import random
import time


PNUM=5 #进程模拟数
CLOCK=0 #时钟周期数
STATE=1 #模拟状态，1为运行0为暂停
LASTRUNSTATE=0 #上个周期整体运行状态，0为未执行，1为执行
pidList=['A','B','C','D','E'] #进程名列表

readyList=[] #新建就绪队列
RRList=[] #为轮转RR建立待执行队列

class PCB:
    def __init__(self,pid,priority,arrTime,serveTime,runTime,waitTime,state): ##初始化进程
        self.pid=pid
        self.priority=priority
        self.arrTime=arrTime
        self.serveTime=serveTime
        self.runTime=runTime
        self.waitTime=waitTime
        self.state=state

    def running(self):      ##进程运行时状态变化
        self.runTime+=1
    def waiting(self):      ##进程等待时状态变化
        self.waitTime+=1


def init(): ##初始化进程，生成五个进程并按到达时间将它们放入就绪队列
    #首先清空各个变量
    global CLOCK
    CLOCK=0
    global STATE
    STATE=0
    global NOWPROCESS
    NOWPROCESS=0
    global RRList
    readyList.clear()
    RRList.clear()

    #随后重新初始化就绪队列
    for i in range(PNUM):
        readyList.append(PCB(pidList[i],1,var[i][0].get(),var[i][1].get(),0,0,'Ready'))
        for j in range(1,4):
            varLbP[i][j].set('NaN')
        bar[i]['value'] = 0
    sortProcessbyArrTime()
    sortProcessLabelbyReadyList()
    messagebox.showinfo(title='提示',message='成功!')

def findBorder(clock):
    t=0
    for i in range(len(readyList)): 
        if(readyList[i].arrTime>clock): #寻找第一个大于CLOck的进程，即寻找不大于CLOCK的进程的个数
            t=i #找到，保存在t中
            break
        t=i+1 #未找到，即全部不大于，个数为等待队列的长度
    return t


def sortProcessLabelbyReadyList():
    for i in range(PNUM):
        rank=ord(readyList[i].pid)-ord('A')
        for j in range(4):
            lbP[rank][j].grid(row=i+1,column=j)
        bar[rank].grid(row=i+1,column=4,pady=28)

def sortProcessbyArrTime(): 
    for i in range(len(readyList)-1):
        for j in range(i+1,len(readyList)):
            if readyList[i].arrTime>readyList[j].arrTime:
                readyList[i],readyList[j]=readyList[j],readyList[i]


def sortProcessbyServeTime(begin,clock):
    t=findBorder(clock)
    for i in range(begin,t-1):
        for j in range(i+1,t):
            if readyList[i].serveTime>readyList[j].serveTime:
                readyList[i],readyList[j]=readyList[j],readyList[i]


def sortProcessbyPriority(begin,clock):
    #print('CLOCK:',clock)
    t=findBorder(clock)
    for i in range(t):
        readyList[i].priority=float(readyList[i].waitTime+readyList[i].serveTime)/readyList[i].serveTime
        #print(readyList[i].pid,readyList[i].priority)
    for i in range(begin,t-1):
        for j in range(i+1,t):
            if readyList[i].priority<readyList[j].priority:
                readyList[i],readyList[j]=readyList[j],readyList[i]

def showInfo(now): 
    pos=ord(readyList[now].pid)-ord('A')
    varLbP[pos][1].set(readyList[now].arrTime+readyList[now].runTime+readyList[now].waitTime)
    varLbP[pos][2].set(readyList[now].runTime+readyList[now].waitTime)
    varLbP[pos][3].set(float(readyList[now].runTime+readyList[now].waitTime)/float(readyList[now].serveTime))


def runProcess(now):
    global LASTRUNSTATE
    LASTRUNSTATE=1
    readyList[now].running() #当前进程执行
    pos=ord(readyList[now].pid)-ord('A')
    bar[pos].step(amount=100.0/readyList[now].serveTime-0.001) #修改进度条
    window.update() #更新窗口

def waitProcess(now,clock):
    for i in range(findBorder(clock)): #修改其他进程状态
        if(i!=now): #若当前时钟周期大于等于进程到达时间且不为当前正在执行的进程，即为等待状态
            readyList[i].waiting()


def FCFS(clock): #先来先服务
    if(findBorder(clock)>=1):
        runProcess(0)        
        waitProcess(0,clock)
    if(readyList[0].runTime>=readyList[0].serveTime): #当前进程已经完成
        showInfo(0)
        readyList.remove(readyList[0]) #移除当前进程


    
def SJF(clock): #最短进程优先
    global LASTRUNSTATE
    if(findBorder(clock)>=1):
        if(not LASTRUNSTATE): #如果上个周期未执行，则应重新排序，否则上个周期执行了，就无需排序（只会继续当前执行的内容或执行完后已经排好序了）
            sortProcessbyServeTime(0,clock)
        runProcess(0)        
        waitProcess(0,clock)
    else: #当前没有可以执行的，即空闲状态
        LASTRUNSTATE=0
    if(readyList[0].runTime>=readyList[0].serveTime): #当前进程已经完成
        showInfo(0)
        readyList.remove(readyList[0]) #移除当前进程
        sortProcessbyServeTime(0,clock+1) #当前周期下已经全部执行完毕，再次进行排序应按照下一周期进行，因此clock+1

def updateQueue(clock): #更新待执行队列
    t=findBorder(clock)
    for i in range(t):
        if readyList[i].priority==1:
            RRList.append(readyList[i].pid)
            readyList[i].priority=0 #利用进程属性区分进程是否已被添加至队列，0代表已添加

def delList():
    count=0
    for i in range(PNUM):
        if readyList[i].priority==2:
            count+=1
    if count==5:  #应删除
        readyList.clear()
def RR(clock): #轮转时间片，与其他三个不同，新开了一个队列用于保存原有进程
    updateQueue(clock)
    if(len(RRList)):
        pos=ord(RRList[0])-ord('A')
        runProcess(pos)        
        print(clock,readyList[pos].pid)

        for i in range(len(RRList)): #修改其他进程状态
            if(ord(RRList[i])-ord('A')!=pos): #若当前时钟周期大于等于进程到达时间且不为当前正在执行的进程，即为等待状态
                readyList[ord(RRList[i])-ord('A')].waiting()

        updateQueue(clock+1)

        if(readyList[ord(RRList[0])-ord('A')].runTime<readyList[ord(RRList[0])-ord('A')].serveTime): #当前进程未完成
            t=RRList.pop(0)
            RRList.append(t)
        else:
            showInfo(ord(RRList[0])-ord('A'))
            readyList[ord(RRList[0])-ord('A')].priority=2 #将优先级设置为2，用于最后的删除
            RRList.pop(0) #移除当前进程

    delList() #检测是否应该删除所有已执行过的进程队列



def HRN(clock):   #高响应权
    global LASTRUNSTATE
    if(findBorder(clock)>=1):
        if(not LASTRUNSTATE): #如果上个周期未执行，则应重新排序，否则上个周期执行了，就无需排序（只会继续当前执行的内容或执行完后已经排好序了）
            sortProcessbyPriority(0,clock)
        runProcess(0)        
        waitProcess(0,clock)
    else: #当前没有可以执行的，即空闲状态
        LASTRUNSTATE=0
    if(readyList[0].runTime>=readyList[0].serveTime): #当前进程已经完成
        showInfo(0)
        readyList.remove(readyList[0]) #移除当前进程
        sortProcessbyPriority(0,clock+1) #当前周期下已经全部执行完毕，再次进行排序应按照下一周期进行，因此clock+1

def run():
    global CLOCK
    if(selected.get()==1):
        FCFS(CLOCK)
    elif(selected.get()==2):
        SJF(CLOCK)
    elif(selected.get()==3):
        RR(CLOCK)
    else:
        HRN(CLOCK)
    CLOCK+=1


def allRun(): #执行到底
    global STATE
    STATE=1
    cpuTime=time.time()
    while STATE and len(readyList)>0:
        if(time.time()-cpuTime>=1/RATE.get()):
            run()
            cpuTime=time.time()
    if(len(readyList)==0):
        messagebox.showinfo(title='提示',message='执行完毕!')

def stop():
    global STATE
    STATE=0

def stepRun():
    if len(readyList)>0:
        run()
    else:
        messagebox.showinfo(title='提示',message='执行完毕!')

def help_message():
    messagebox.showinfo(
        title='Help', message='Please contact me via christopherzh123@163.com')


def about_message():
    messagebox.showinfo(
        title='About', message='      Author:Zihang Zhang')


window = tk.Tk() # 实例化object，建立窗口window

window.title('处理器调度')

window.geometry('1080x720') # 设定窗口的大小

RATE=tk.IntVar() #速率设置
RATE.set(3)

#放置三个框架，分别为输入、结果展示、控制模块
frmInput=tk.LabelFrame(window,width=300,height=420)
frmInput.place(x=780,y=0)

frmResult=tk.LabelFrame(window,width=780,height=720)
frmResult.place(x=0,y=0)

frmControl=tk.LabelFrame(window,width=300,height=300)
frmControl.place(x=780,y=420)


#渲染输入表格
lbArr=tk.Label(frmInput, text='到达时间',font=('Songti', 12))
lbArr.grid(row=0,column=1,padx=13, pady=25)
lbSer=tk.Label(frmInput, text='服务时间',font=('Songti', 12))
lbSer.grid(row=0,column=3,padx=13, pady=25)
lbList=[]
for i in range(PNUM):
    lbList.append(tk.Label(frmInput, text=pidList[i],font=('Songti', 12)).grid(row=1+i,column=0, padx=15,pady=20))
btnConfirm=tk.Button(frmInput, text="输入完毕",command=init)
btnConfirm.grid(row=PNUM+1,column=2)

#初始化数据
var=[] #输入进程的信息
spin=[] #Spinbox列表，用于存储SpinBox控件，共五个
#initList=[[0,4],[1,3],[2,5],[3,2],[4,4]]
initList=[[0,3],[2,6],[4,4],[6,5],[8,2]]
#initList=[[5,3],[2,6],[4,6],[6,5],[8,2]]
#设置输入模块，五个进程分别对应五个栏目，10个变量
for i in range(PNUM):
    varr=[] #存储内层变量，共两个，分别为到达时间与服务时间
    spinn=[] #存储内层spinbox
    for j in range(2):
        varr.append(tk.IntVar())
        varr[j].set(initList[i][j])
        spinn.append(tk.Spinbox(frmInput, from_=0, to=15, width=8,textvariable=varr[j]))
        spinn[j].grid(row=1+i,column=1+2*j)
    var.append(varr)
    spin.append(spinn)


# 设置算法选择栏
selected = tk.IntVar()
selected.set(1)
l=['FCFS','SJF','RR','HRN']
for i in range(1,5):
    tk.Radiobutton(frmControl, text=l[i-1], value=i, variable=selected).place(relx=0.4, rely=0.1*i)

rateLabel=tk.Label(frmControl, text="速率",font=('Songti', 12)).place(relx=0.3,rely=0.85)
rate = tk.Spinbox(frmControl, from_=0, to=100, width=7,textvariable=RATE).place(relx=0.5,rely=0.85)#设置速率选择栏

#设置功能选择栏
btnAllRun = tk.Button(frmControl, text="执行到底",command=lambda:allRun())
btnStepRun = tk.Button(frmControl, text="步进执行",command=lambda:stepRun())
btnStop = tk.Button(frmControl, text="   停止   ",command=lambda:stop())
btnReset = tk.Button(frmControl, text="   复位   ",command=lambda:init())
btnAllRun.place(relx=0.2, rely=0.5)
btnStepRun.place(relx=0.6, rely=0.5)
btnStop.place(relx=0.2, rely=0.7)
btnReset.place(relx=0.6, rely=0.7)

#渲染结果展示栏
lbPid=tk.Label(frmResult, text='进程号',font=('Songti', 12))
lbPid.grid(row=0,column=0,padx=35)
lbCom=tk.Label(frmResult, text='完成时间',font=('Songti', 12))
lbCom.grid(row=0,column=1,padx=35)
lbRun=tk.Label(frmResult, text='周转时间',font=('Songti', 12))
lbRun.grid(row=0,column=2,padx=35)
lbPRun=tk.Label(frmResult, text='带权周转时间',font=('Songti', 12))
lbPRun.grid(row=0,column=3,padx=35)
lbPro=tk.Label(frmResult, text='进程执行进度',font=('Songti', 12))
lbPro.grid(row=0,column=4,padx=48)


lbP=[] #进程展示label列表
varLbP=[] #进程展示label所用到的var列表
barlength=170 #进度条长度
bar=[] #进度条列表
for i in range(PNUM):
    varLbPP=[] #内层进程变量列表，用于生成一列
    lbPP=[] #内层进程列表，用于生成一列
    #第一列到四列
    for j in range(4):
        varLbPP.append(tk.StringVar())
        if j==0:
            varLbPP[j].set(pidList[i])
        else:
            varLbPP[j].set('NaN')
        lbPP.append(tk.Label(frmResult,textvariable=varLbPP[j],font=('Songti', 12)))
        lbPP[j].grid(row=i+1,column=j)
    varLbP.append(varLbPP)
    lbP.append(lbPP)
    #第五列进程进度条
    bar.append(Progressbar(frmResult, length=barlength))
    bar[i].grid(row=i+1,column=4,pady=28)


#提示信息
lHelp = tk.Label(window, text="电计1806张子航 201873049\n\n左上角为进程模拟调度结果\n\n右上角为进程输入\n\n右下角为算法与功能选择", 
font=('SongTi', 15)) # 在图形界面上设定标签
lHelp.place(relx=0.25,rely=0.65)# 放置标签



menubar = tk.Menu(window) # 创建一个菜单栏

filemenu = tk.Menu(menubar, tearoff=0) # 创建一个File菜单项
menubar.add_cascade(label='文件', menu=filemenu) # 将上面定义的空菜单命名为File，放在菜单栏中，就是装入那个容器中

submenu = tk.Menu(filemenu, tearoff=0)  # 在File上创建菜单
filemenu.add_command(label='上传')


filemenu.add_command(label='退出', command=window.quit)

runmenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='运行', menu=runmenu)

helpmenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='关于', menu=helpmenu)
helpmenu.add_command(label='帮助', command=help_message)
helpmenu.add_command(label='关于', command=about_message)

window.config(menu=menubar) # 创建菜单栏完成后，配置让菜单栏menubar显示出来

window.mainloop() # 主窗口循环显示

