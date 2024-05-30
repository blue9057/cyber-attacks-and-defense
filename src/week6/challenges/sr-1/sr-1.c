#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

int input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  int i;

  printf("I would like to let you have the sequential read capability to\n"
          "my current stack. How many bytes of your name do you want to print?\n");
  scanf("%d", &i);
  write(1, buf, i);

  printf("Please type your name: \n");
  read(0, buf, BUFSIZE * 2);

  return 0;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
