#include "kernel/types.h"
#include "user/user.h"


int main (int argc, char* argv) {

<<<<<<< HEAD
   int p1[2];
   pipe(p1);
   char buf = 't';
   int pid = fork();
   if (pid > 0) {   
       write(p1[1], &buf, 1);
=======
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

>>>>>>> be5fc4332f9c3c933256c8384d827a1f795d2204
       int i = 0;
       wait(&i);
       read(p1[0], &buf, 1);
       fprintf(1, "%d: received pong\n", getpid());
       exit(1);
<<<<<<< HEAD
   }
   else {
      read(p1[0], &buf, 1);
	   fprintf(1, "%d: received ping\n", getpid());
	   write(p1[1], &buf, 1);
	   exit(1);
   }
=======
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
>>>>>>> be5fc4332f9c3c933256c8384d827a1f795d2204
}
