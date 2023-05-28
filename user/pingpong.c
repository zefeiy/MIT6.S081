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
	char buf = 't';
       //close(p1[0]);
       //close(p2[1]);
       if( write(p1[1], &buf, 1) != 1) {
	   fprintf(1, "Usage: write failed...\n");
	   exit(1);
        }
       
       if( read(p2[0], &buf, 1) == 1 ) {
           fprintf(1, "%d :received pong\n", getpid());
       }
       int i = 0;
       wait(&i);
       close(p1[1]);
       close(p2[0]);
       exit(1);
    }
    else {
    	    //close(p1[1]);
	    //close(p2[0]);
	    char buf = 't';
            read(p1[0], &buf, 1);
	    fprintf(1, "%d :received ping\n", getpid());
	    write(p2[1], &buf, 1);
	    close(p1[0]);
	    close(p2[1]);
	    exit(1);
         }	
    exit(1);
}
