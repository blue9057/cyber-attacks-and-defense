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

int some_function() {
  system("ls");
}


__attribute__((optimize("-O2"))) int input_func(int a) {
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("Please type your name: \n");

  // OVERFLOW!!!!!!
  read(0, buf, BUFSIZE * 2);

  printf("Hello %s!\n", buf);

  return 0;
}

int non_main_func(void) {
  int a = 0;
  return input_func(a);
}

int main(int argc, char** argv, char** envp) {
  // get permission
  setregid(getegid(), getegid());
  non_main_func();
  return 0;
}
