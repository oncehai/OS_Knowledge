#include "init.h"

// 创建守护进程
void daemonize(const char* cmd){
    int                     i, fd0, fd1, fd2;
    pid_t                   pid;
    struct rlimit           rl;
    struct sigaction        sa;

    // 清除进程的 umask 以确保当守护进程创建文件和目录时拥有所需的权限。
    umask(0);

    // 获取文件描述符数量的最大值
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0){
        // printf("%s: can't get file limit \n", cmd);
        exit(1);
    }

    // 执行一个 fork()，之后父进程退出，子进程继续执行。
    if((pid = fork()) < 0){
        // printf("%s: can't fork \n", cmd);
        exit(1);
    }else if(pid != 0){     // parent
        exit(0);
    }

    // 子进程调用 setsid() 开启一个新会话
    // 成为新会话的leader，并且断开所有控制终端
    // 子进程会继承父进程的会话和控制终端，新建会话可以与原有的会话和终端脱离。当原有会话结束，新会话不受影响
    if(setsid() == -1){
        // printf("%s: can't setsid \n");
        exit(1);
    }

    // 暂时不太明白
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        // printf("%s: can't ignore SIGHUB \n", cmd);
        exit(1);
    }
    // 再次创建子进程，确保未来该会话不会分配控制终端。只有会话的leader才有权限分配控制终端
    if((pid = fork()) < 0){
        // printf("%s: can't fork \n", cmd);
        exit(1);
    }else if(pid != 0){     // parent
        exit(0);
    }

    // 更改进程的工作目录，避免当前的工作目录被守护进程阻止无法卸载文件系统
    if (chdir("/") < 0){
		// printf("%s: can't change directory to / \n", cmd);
        exit(1);
    }

    // 关闭所有文件描述符
    // 关闭守护进程从其父进程继承而来的所有打开着的文件描述符。
    if (rl.rlim_max == RLIM_INFINITY)
		// rl.rlim_max = 1024;
		rl.rlim_max = 20;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

    // 绑定文件描述符0，1，2到 /dev/null
    // 在关闭了文件描述符0、1、2之后，守护进程通常会打开/dev/null 并使用dup2() 使所有这些描述符指向这个设备。
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

}
