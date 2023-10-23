#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#ifndef BUFSIZE
#define BUFSIZE 30
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

uint32_t eip;

__attribute__((optimize("-O2"))) int input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("Where do you like to jump? Put a hexadeximal address.. \n");
  uint32_t addr;
  scanf("%x", &addr);
  ((int(*)())addr)();
  return 0;
}

int main(int argc, char** argv, char** envp) {
  uint32_t end = 0xffffe000;
  uint32_t start = &argc;
  memset(&argc, 0, end-start);
  input_func();
  return 0;
}
