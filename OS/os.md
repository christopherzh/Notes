# 基础概念
## 进程
进程是处于执行期的程序以及相关的资源的总称。实际上，进程就是正在执行的程序代码的实时结果。

进程本质上是正在执行的程序，与每个进程相关的是地址空间，在这个地址空间中，进程可对其读写，其存放着可执行程序、程序的数据以及程序堆栈。

通常进程还要包含其他资源，像打开的文件，挂起的信号，内核内部数据，处理器状态，一个或多个具有内存映射的内存地址空间及一个或多个执行进程。(thread of execution)

现代操作系统中，进程提供两种虚拟机制：虚拟处理器和虚拟内存。虚拟处理器给进程假象，让其认为自己在独享处理器，虚拟内存让进程在分配和管理和内存时觉得自己拥有整个系统的所有内存资源。在线程之间（同一个进程间的）可以共享虚拟内存，但每个都拥有各自的虚拟处理器。
## 线程
执行线程，简称线程，是在进程中的活动对象，每个进程都拥有都拥有一个独立的程序计数器、进程栈和一组进程寄存器，内核调度的对象是线程。
## 地址空间
## 文件