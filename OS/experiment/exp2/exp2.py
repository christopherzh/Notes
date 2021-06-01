import tkinter as tk
import tkinter.messagebox as messagebox
from tkinter.ttk import Progressbar
from tkinter import ttk
import random
import time
RATE=3
PNUM=5
CLOCK=0
pidList=['A','B','C','D','E']
class PCB:
    def __init__(self,pid,priority,arrTime,serveTime,runTime,waitTime,state): ##初始化进程
        self.pid=pid
        self.priority=priority
        self.arrTime=arrTime
        self.serveTime=serveTime
        self.runTime=runTime
        self.waitTime=waitTime
        self.state=state
    
    def setRun(self):    ##将状态置为Run
        self.state='Run'

    def setFinish(self):     ##将状态置为Finish
        self.state='Finish'

    def setReady(self):      ##将状态置为Ready
        self.state='Ready'

    def running(self):      ##进程运行时状态变化
        self.runTime+=1
    def waiting(self):      ##进程等待时状态变化
        self.waitTime+=1


def init(): ##初始化进程，生成五个进程并按到达时间将它们放入就绪队列
    readyList.clear()
    global CLOCK
    CLOCK=0
    for i in range(PNUM):
        readyList.append(PCB(pidList[i],1,var[i][0].get(),var[i][1].get(),0,0,'Ready'))
        print(var[i][0].get(),var[i][1].get());
        for j in range(1,4):
            varLbP[i][j].set('NaN')
        bar[i]['value'] = 0
    for i in range(len(readyList)-1):
        for j in range(i+1,len(readyList)):
            if readyList[i].arrTime>readyList[j].arrTime:
                readyList[i],readyList[j]=readyList[j],readyList[i]
    sortProcessbyArrTime()

def sortProcessbyArrTime():
    for i in range(PNUM):
        rank=ord(readyList[i].pid)-ord('A')
        for j in range(4):
            lbP[rank][j].grid(row=i+1,column=j)
        bar[rank].grid(row=i+1,column=4,pady=28)

def FCFS(): #先来先服务
    pos=ord(readyList[0].pid)-ord('A')
    if(readyList[0].runTime>=readyList[0].serveTime): #当前进程已经完成
        varLbP[pos][1].set(readyList[0].arrTime+readyList[0].runTime+readyList[0].waitTime)
        varLbP[pos][2].set(readyList[0].runTime+readyList[0].waitTime)
        varLbP[pos][3].set(float(readyList[0].runTime+readyList[0].waitTime)/float(readyList[0].serveTime))
        readyList.remove(readyList[0]) 

        if(len(readyList)>=1): #当前周期下还应运行一个新的进程
            readyList[0].running()
            bar[ord(readyList[0].pid)-ord('A')].step(amount=100.0/readyList[0].serveTime-0.001) #修改进度条
    else:
        readyList[0].running()
        bar[pos].step(amount=100.0/readyList[0].serveTime-0.001) #修改进度条
    window.update()
    for i in range(1,len(readyList)): #修改其他进程状态
        if(readyList[i].arrTime<=CLOCK): #若当前时钟周期大于等于进程到达时间，即为等待状态
            readyList[i].waiting()

    
def SJF(): #最短进程优先
    pass
def RR():
    pass
def HRN():   
    pass



def allRun(): #执行到底
    cpuTime=time.time()
    while len(readyList)>0:
        if(time.time()-cpuTime>=1/RATE):
            if(selected.get()==1):
                FCFS()
            elif(selected.get()==2):
                SJF()
            elif(selected.get()==3):
                RR()
            else:
                HRN()
            cpuTime=time.time()
            global CLOCK
            CLOCK+=1
            
def stop():
    pass
def stepRun():
    pass


def help_message():
    messagebox.showinfo(
        title='Help', message='Please contact me via christopherzh123@163.com')


def about_message():
    messagebox.showinfo(
        title='About', message='      Author:Zihang Zhang')


window = tk.Tk() # 实例化object，建立窗口window

window.title('处理器调度')

window.geometry('1080x720') # 设定窗口的大小


'''
var = tk.StringVar()
var.set('Please enter!')
l = tk.Label(window, textvariable=var, font=('Arial', 12), width=30, height=4) # 在图形界面上设定标签
l.grid(row=0, column=0) # 放置标签
'''
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

var=[] #输入进程的信息
spin=[] #Spinbox列表，用于存储SpinBox控件，共五个
initList=[[0,3],[2,6],[4,4],[6,5],[8,2]]
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

readyList=[]



# 设置算法选择栏
selected = tk.IntVar()
l=['FCFS','SJF','RR','HRN']
for i in range(1,5):
    tk.Radiobutton(frmControl, text=l[i-1], value=i, variable=selected).place(relx=0.4, rely=0.1*i)
'''
rad1 = tk.Radiobutton(frmControl, text="FCFS", value=1, variable=selected)
rad2 = tk.Radiobutton(frmControl, text="SJF", value=2, variable=selected)
rad3 = tk.Radiobutton(frmControl, text="RR", value=3, variable=selected)
rad4 = tk.Radiobutton(frmControl, text="HRN", value=4, variable=selected)
rad1.place(relx=0.4, rely=0.1)
rad2.place(relx=0.4, rely=0.2)
rad3.place(relx=0.4, rely=0.3)
rad4.place(relx=0.4, rely=0.4)
'''

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
'''
style = ttk.Style()
style.theme_use('default')
'''
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

