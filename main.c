#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main() {
  //parent process
  int f;
  f = fork();
  if (f == 0) {
    int p = getpid(); 
    printf("child pid: %d\n", p); 
    srand( time(NULL) ); 
    int rand_int = (rand()%15) + 5; 
    sleep(rand_int);
    printf("child %d is done\n", p); 
    return rand_int;
  }
  else {
    printf("I am a parent\n"); 
    f = fork(); 
    int a; 
    wait(&a);  
    printf("child %d was asleep for %d seconds\n", f, WEXITSTATUS(a));
    printf("parent %d is done\n", getpid());
    exit(1);
  }
  return 0; 
}
