#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFSIZE
#define BUFSIZE 30
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

__attribute__((optimize("-O2"))) int input_func(int a) {
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("Your buffer is at: %p\n", buf);
  printf("Please type your name: \n");
  read(0, buf, BUFSIZE * 2);

  printf("Hello %s\n!", buf);

  return 0;
}

int non_main_func(void) {
  int a = 0;
  return input_func(a);
}

int main(int argc, char** argv, char** envp) {
  non_main_func();
  return 0;
}
