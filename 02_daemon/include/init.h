#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/resource.h>
#include <signal.h>

// 创建守护进程
void daemonize(const char* cmd);