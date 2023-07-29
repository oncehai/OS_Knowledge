#include "apue.h"
#include <sys/wait.h>

int main(void){
    pid_t pid;
    if((pid = fork()) < 0){
        printf("fork error \n");
    }else if(pid == 0){     // child
        printf("child.--- \n");
        // 如果执行sh脚本时或者解释器文件时，需要注意相应权限,
        // 且执行解释器文件时,该函数的第二个参数,也就是arg[0]不执行
        if(execl("/home/pi/work/learn/01_interpreter/testinterp.sh", 
        // if(execl("/home/pi/work/learn/01_interpreter/echoarg", 
        "testinterp", "myarg1", "MY ARG2", (char*)0) < 0){
            printf("execl error \n");
        }
    }
    printf("parent.--- \n");
    if(waitpid(pid, NULL, 0) < 0){  // parent
        printf("waitpid error \n");
    }
    exit(0);
}