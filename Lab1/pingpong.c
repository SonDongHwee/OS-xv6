#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char** argv){
    if(argc != 1){
        fprintf(2, "usage: pingpong ...\n");
        exit(1);    
    }
    char buffer[128];

    int parentfd[2];
    int childfd[2];
    pipe(parentfd); pipe(childfd);

    if(fork() == 0){
        /* Child */
        close(parentfd[1]); /* child do not use parent's write pipe (but not necessary; this syscall makes a time delay)*/
        read(parentfd[0],buffer,4);
        printf("%d: received %s\n",getpid(),buffer);
        write(childfd[1],"pong",4);

    }else{
        /* Parent */
        close(childfd[1]); /* parent do not use child's write pipe (but not necessary; this syscall makes a time delay)*/
        write(parentfd[1],"ping",4);
        read(childfd[0],buffer,4);
        printf("%d: received %s\n",getpid(),buffer);
    }
    exit(0);
}