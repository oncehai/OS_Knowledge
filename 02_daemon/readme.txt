创建守护进程案例
本案例用于构建守护进程，并实现每2秒获取当前系统时间并写到本地文件中

过程:
1.编辑保存init.h, init.c, writeCurTime.c文件,
并调用(g++ writeCurTime.c init.c -Iinclude -o echoarg)进行编译.

2.运行程序./writeCurTime

3.查看进程是否运行 ps -efj | grep writeCurTime
(-e 显示所有进程； -f 显示程序间关系； -j 显示与作业有关的信息：会话id、进程组id、控制终端、以及终端进程组id)
运行结果：
**@**:~/**/02_daemon $ ps -efj | grep writeCurTime
pi          7795       1    7794    7794 40 13:44 ?        00:00:03 ./writeCurTime
pi          7844    7578    7843    7578  0 13:45 pts/3    00:00:00 grep --color=auto writeCurTime

4.关闭该进程 kill -9 7795
(****为该守护进程的id) 
(-9 (KILL)：杀死一个进程。)