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

int stack_cookie = 0xfaceb00c;
int retrieved_cookie = 0;

__attribute__((optimize("-O2"))) int input_func(int a) {
  // name buffer to overflow
  asm volatile("mov %0, -0x4(%%ebp)"::"r"(stack_cookie):);
  char buf[BUFSIZE];
  printf("Please type your name: \n");
  // OVERFLOW!!!
  read(0, buf, BUFSIZE * 2);

  printf("Hello %s!\n", buf);

  asm volatile("mov -0x4(%%ebp), %0":"=r"(retrieved_cookie)::);

  if(retrieved_cookie != stack_cookie) {
    printf("Stack smash detected!\n");
    exit(-1);
  }
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
