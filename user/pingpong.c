#include "kernel/types.h"
#include "user/user.h"


int main (int argc, char* argv) {

   int p1[2];
   pipe(p1);
   char buf = 't';
   int pid = fork();
   if (pid > 0) {   
       write(p1[1], &buf, 1);
       int i = 0;
       wait(&i);
       read(p1[0], &buf, 1);
       fprintf(1, "%d: received pong\n", getpid());
       exit(1);
   }
   else {
      read(p1[0], &buf, 1);
	   fprintf(1, "%d: received ping\n", getpid());
	   write(p1[1], &buf, 1);
	   exit(1);
   }
}
