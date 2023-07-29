该文件测试解释器文件以及解释器的简单应用案例。
内容：
1.创建解释器，并进行编译
2.创建解释器脚本

过程:
1.编辑保存echoarg.c文件,并调用(g++ echoarg.c -Iinclude echoarg)进行编译.
2.保存testinterp.sh文件,并更改该文件的执行权限.
3.编辑保存main_file.c文件,并调用(g++ main_file.c -Iinclude main_file)进行编译.
4.执行脚本(./main_file 或者 ./main_file > 123.txt)

注意事项：
1.如果运行是缺失文件，可参考博客url: https://blog.csdn.net/qq_41899773/article/details/107376991 
2.在运行解释器文件时,需要更改文件的运行权限,否则通过execl调用时不能正常执行.
3.通过execl执行解释器文件时,需要注意函数的excel的第二个参数,即arg0会直接抛弃.
execl函数原型: int execl(const char *pathname, const char *arg0, ...);