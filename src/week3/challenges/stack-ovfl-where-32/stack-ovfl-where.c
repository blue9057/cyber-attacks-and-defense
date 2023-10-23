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
  printf("Your buffer is at: %p\n", buf);
  printf("Please type your name: \n");
  read(0, buf, 0x26 * 2);

  printf("Hello %s\n!", buf);

  asm volatile("mov 0x4(%%ebp), %0" :  "=r"(eip) ::);
  if((eip & 0xfffff000) != 0x8048000) {
    printf("Your changed EIP is at %p. I only accept the address that starts with 0x8048XXX\n", eip);
    exit(-1);
  }
  printf("EIP is %p\n", eip);
  return 0;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
