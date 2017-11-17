#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

int randint() {
  int fd = open("/dev/random", O_RDONLY);
  int buffer;
  read(fd, &buffer, sizeof(int));
  if (errno) {
    printf("%s", strerror(errno));
  }
  buffer = abs(buffer%15 + 5);
  close(fd);
  return buffer;
}

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
      int p = getpid();
      printf("child pid: %d\n", p);
      int rand_int = randint();
      sleep(rand_int);
      printf("child %d is done\n", p);
      return rand_int;
    }
  }
  else {
    int p = getpid();
    printf("child pid: %d\n", p);
    int rands = randint();
    sleep(rands);
    printf("child %d is done\n", p);
    return rands;
  }
  return 0;
}
