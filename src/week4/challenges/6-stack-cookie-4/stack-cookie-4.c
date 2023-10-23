#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

char g_buf[BUFSIZE * 2];

int input_func(int a) {
  // name buffer to overflow
  int length = 0;
  char buf[BUFSIZE];
  int *i = (int*)(&buf[BUFSIZE]);      // overwrite this variable!
  printf("Please type your name: \n");
  length = read(0, g_buf, BUFSIZE * 2);
  for(*i=0; *i<length; (*i)++) {
      buf[*i] = g_buf[*i];
  }
  printf("Hello %s!\n", buf);

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
