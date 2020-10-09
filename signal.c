/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void handler(int signum){ //signal handler
  printf("Hello World!\n");
  printf("Turing was right!\n");
  exit(1); //exit after printing
}
void timer(int signum){
double total_seconds = 0.0;
clock_t start = clock();
  signal(SIGALRM, handler);
clock_t end = clock();
total_seconds += (double)(end - start) / CLOCKS_PER_SEC;
  printf("Total time it took the program to execute is %f seconds\n", total_seconds);
  exit(1);
}

int main(int argc, char * argv[]){
  signal(SIGINT, timer);  //register timer to handle SIGINT
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(1); //busy wait for signal to be delivered
  return 0; //never reached
}