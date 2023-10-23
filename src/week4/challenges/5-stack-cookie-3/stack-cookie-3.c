#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

int input_func(int a) {

  // check assembly. GCC Stack cookie is here.

  size_t size;
  printf("How many bytes do you want to read?\n");
  scanf("%lu", &size);
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("Reading %lu bytes: \n", size);
  read(0, buf, size);

  printf("Hello %s!\n", buf);

  // check assembly. GCC Stack cookie is here.

  return 0;
}

int non_main_func(void) {
  int i = 2000;
  while(i) {
    printf("You have %d trials left\n", i--);
    int pid = fork();
    if(!pid) {
      input_func(0);
      // exit with zero if you do not change the return address
      exit(0);
    }
    else {
      int status = 0;
      waitpid(pid, &status, 0);
      printf("Exit status: %d\n", status);
    }
  }
}

int main(int argc, char** argv, char** envp) {
  non_main_func();
  return 0;
}
