#include "kernel/types.h"
#include "user/user.h"

#define MAXSIZE 36


void is_prime(int pipe_read, int pipe_write) {
    char num[MAXSIZE];
    int val = 0;
    read(pipe_read, num, MAXSIZE);

    for (int i=2; i<MAXSIZE; ++i) {
        if(num[i] == '1') {
            val = i;  //找第一个质数
            break;
        }
    }
    if(val == 0) {
        close(pipe_read);
        close(pipe_write);
        exit(1);
    }

    printf("prime %d\n", val); 
    num[val] = '0';  //避免重复寻找同一个质数
    
    for(int i=2; i<MAXSIZE ;++i) {
        if( i % val == 0)
            num[i] = '0'; // 划去所有的倍数
    }
    int pid = fork();

    if(pid > 0) {
        write(pipe_write, num, MAXSIZE);
        close(pipe_write);
        close(pipe_read);
        wait(0);
    }
    else {
        is_prime(pipe_read, pipe_write);
    }
}
 int main (int argc, char* argv[]) {
    int fd[2];
    pipe(fd);
    char buf[MAXSIZE];
    for(int i=0; i<36; ++i) {
        buf[i] = '1';  //全是质数
    }
    buf[0] = '0';
    buf[1] = '0';
    int pid = fork();

    if (pid > 0) {
        close(fd[0]); 
        write(fd[1], buf, MAXSIZE);
        close(fd[1]);
        wait(0);
    }
    else {
        is_prime(fd[0], fd[1]);
        wait(0);
    }

    exit(1);
 }