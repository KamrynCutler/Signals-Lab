#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MAX 3

void SIGINT_handler(int sig) {
  printf("\nIn Child %d - Caught SIGINT!\n", getpid());
  exit(1);
}

void main(int argc, char *argv[]){

  int pid[MAX];
  int status;
  int i;
  
  sigset_t cmask, origmask;
 
  for(i = 0; i < MAX; i++){
    pid[i] = fork();  //creates a child
    srandom(getpid());
 
    switch(pid[i]){
      case 0:    //child
       /* 
        sigaddset (&cmask, SIGTERM);
        sigaddset (&cmask, SIGINT);
        sigaddset (&cmask, SIGHUP);
        sigaddset (&cmask, SIGUSR1);
        
        if (sigprocmask(SIG_BLOCK, &cmask, &origmask) < 0 {
          printf("Error\n");
        }
      */
        signal(SIGINT, SIGINT_handler);
        
        printf("In child, pid = %d, parent pid = %d ...\n", getpid(), getppid());
      //  sleep(random() % 3);
        pause();
        printf("Child executing \"ls -l\"...\n");
       /*     
        if (sigprocmask(SIG_SETMASK, &origmask, 0) < 0 {
          printf("Error\n");
        }  
       */     
        execl("/bin/ls","ls","-l", (char *)0);
     // exit(0);
        break;

      case -1:  //error
        break;

      default:  //parent process, PID is child's pid
        break;
    }
   
  }
  
  for(i = 0; i < MAX; i++){
      kill(pid[i], SIGINT);
//    kill(getpid(), SIGINT);
    
    printf("Parent waiting on Child pid = %d...\n", pid[i]);
    wait(&status);  //parent waits until child terminates, then reaps the child
    printf("Child pid = %d terminated with status = %d\n", pid[i], status);
  }
  
  printf("Parent terminating: Child status = %d\n",status);
  
}
