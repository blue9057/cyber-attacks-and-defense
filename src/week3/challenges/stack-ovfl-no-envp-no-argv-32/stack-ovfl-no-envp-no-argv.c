#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFSIZE
#define BUFSIZE 30
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

__attribute__((optimize("-O2"))) int input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("Please type your name: \n");
  read(0, buf, 20);

  printf("Hello %s\n!", buf);

  return 0;
}

int main(int argc, char** argv, char** envp) {
  char **env = envp;
  while(*env != NULL) {
    memset(*env, 0, strlen(*env));
    ++env;
  }

  char **arg = argv;
  while(*arg != NULL) {
    memset(*arg, 0, strlen(*arg));
    ++arg;
  }

  input_func();
  return 0;
}
