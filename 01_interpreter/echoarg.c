#include "apue.h"

int main(int argc, char *argv[]){
    int i;
    // echo all command-line args
    for(i=0; i<argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    exit(0);
}

// http://www.apuebook.com/src.3e.tar.gz