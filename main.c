#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main() {
  //parent process
  int f;
  f = fork();
  if (f) {
    printf("I am a parent\n");
    int a;
    wait(&a);
    printf("child %d was asleep for %d seconds\n", f, WEXITSTATUS(a));
    f = fork();
    if(f){
      int b;
      wait(&b);
      printf("child %d was asleep for %d seconds\n", f, WEXITSTATUS(b));
      printf("parent %d is done\n", getpid());
      exit(1);
    }
    else{
      srand( time(NULL) );
      int p = getpid();
      printf("child pid: %d\n", p);
      int rand_int = (rand()%15) + 5;
      sleep(rand_int);
      printf("child %d is done\n", p);
      return rand_int;
    }
  }
  else {
    srand( time(NULL) );
    int p = getpid();
    printf("child pid: %d\n", p);
    int rand_int = (rand()%15) + 5;
    sleep(rand_int);
    printf("child %d is done\n", p);
    return rand_int;
  }
  return 0;
}
