#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char* argv) {

    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if (pid > 0) {
	    char* buf = "ping";
        close(p1[0]);
        close(p2[1]);
        write(p1[1], buf, 5);
        read(p2[0], buf, 5);
        fprintf(1, "%d :received %s\n", getpid(), buf);

       int i = 0;
       wait(&i);
       close(p1[1]);
       close(p2[0]);
       exit(1);
    }
    else {
        close(p1[1]);
	    close(p2[0]);
	    char* buf = 'pong';
            read(p1[0], buf, 5);
	    fprintf(1, "%d :received %s\n", getpid(), buf);
	    write(p2[1], buf, 5);
	    close(p1[0]);
	    close(p2[1]);
	    exit(1);
    }	
    exit(1);
}
