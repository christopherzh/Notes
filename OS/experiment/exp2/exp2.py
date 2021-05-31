import tkinter as tk
import tkinter.messagebox as messagebox
import tkinter.filedialog as filedialog
import random


def upload_video():
    selectFile = filedialog.askopenfilename()
    entry1.insert(0, selectFile)
    global upload_count
    upload_count += 1


def upload_audio():
    selectFile = filedialog.askopenfilename()
    entry2.insert(0, selectFile)
    global upload_count
    upload_count += 1


def upload_text():
    selectFile = filedialog.askopenfilename()
    entry3.insert(0, selectFile)
    global upload_count
    upload_count += 1


def help_message():
    messagebox.showinfo(
        title='Help', message='Please contact me via christopherzh123@163.com')


def about_message():
    messagebox.showinfo(
        title='About', message='      Author\nZihang Zhang\nJiatong Zhang\nPanhong Ren')


upload_count = 0
# 实例化object，建立窗口window
window = tk.Tk()

window.title('MultiModal Sentiment Analysis Application')

# 设定窗口的大小
window.geometry('600x380')

photo = tk.PhotoImage(file="OS/experiment/exp2/bg.png")
background_label = tk.Label(window, image=photo)
background_label.place(x=0, y=0, relwidth=1, relheight=1)


var = tk.StringVar()
var.set('Please upload to run analysis procedure \nbelow or in the menu')
# 在图形界面上设定标签
l = tk.Label(window, textvariable=var, font=('Arial', 12), width=30, height=4)

# 放置标签
l.pack()  # grid(row=0, column=0)
b_upload_video = tk.Button(window, text="Video Upload", command=upload_video)
b_upload_video.pack(padx='1', pady='2')  # grid(row=1, column=0)
entry1 = tk.Entry(window, width='40')
entry1.pack(padx='1', pady='5')  # grid(row=1, column=1)
b_upload_audio = tk.Button(window, text="Audio Upload", command=upload_audio)
b_upload_audio.pack(padx='1', pady='2')
entry2 = tk.Entry(window, width='40')
entry2.pack(padx='1', pady='5')  # grid(row=1, column=1)
b_upload_text = tk.Button(window, text="Text Upload", command=upload_text)
b_upload_text.pack(padx='1', pady='4')
entry3 = tk.Entry(window, width='40')
entry3.pack(padx='1', pady='5')  # grid(row=1, column=1)
# 创建一个菜单栏
menubar = tk.Menu(window)

# 创建一个File菜单项
filemenu = tk.Menu(menubar, tearoff=0)
# 将上面定义的空菜单命名为File，放在菜单栏中，就是装入那个容器中
menubar.add_cascade(label='File', menu=filemenu)

submenu = tk.Menu(filemenu, tearoff=0)  # 在File上创建菜单
filemenu.add_cascade(label='Upload', menu=submenu, underline=0)

submenu.add_command(label='Video Upload', command=upload_video)
submenu.add_command(label='Audio Upload', command=upload_audio)
submenu.add_command(label='Text Upload', command=upload_text)

filemenu.add_command(label='Exit', command=window.quit)

runmenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='Run', menu=runmenu)

helpmenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='Help', menu=helpmenu)
helpmenu.add_command(label='Help', command=help_message)
helpmenu.add_command(label='About', command=about_message)
# 创建菜单栏完成后，配置让菜单栏menubar显示出来
window.config(menu=menubar)
# 主窗口循环显示
window.mainloop()
# 注意，loop因为是循环的意思，window.mainloop就会让window不断的刷新，如果没有mainloop,就是一个静态的window,传入进去的值就不会有循环，mainloop就相当于一个很大的while循环，有个while，每点击一次就会更新一次，所以我们必须要有循环
# 所有的窗口文件都必须有类似的mainloop函数，mainloop是窗口文件的关键的关键。
