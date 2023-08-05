#include "init.h"

#define MAXPATH 512

/**
 * 创建守护进程，每2s存储一下当前时间
 * 
*/

int main(){
    // char*       path;
    char        path[MAXPATH];
    // size_t      size;
    // size = 512;
    char        filepath[MAXPATH];
    FILE*       file;

    printf("writeCurTime begining... \n");

    // 获取当前工作目录
    if(getcwd(path, sizeof(path)) == NULL){
        // printf("getcwd fail!\n");
        exit(1);
    }
    printf("path:\t%s \n", path);

    // 存储文件的路径
    sprintf(filepath, "%s/time.txt", path);
    printf("filepath:\t%s \n", filepath);

    // 创建守护进程
    daemonize("writeCurTime");
    
    file = fopen(filepath, "a+");
    if(file == NULL){
        // printf("fopen fail! \n");
        exit(1);
    }

    while (1)
    {
        time_t tt = time(NULL);
        struct tm t = *localtime(&tt);

        fprintf(file, "现在是北京时间: %d-%d-%d %d:%d:%d\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        fflush(file); // 保证数据立即写入文件

        sleep(2);
    }

    return 0;
}