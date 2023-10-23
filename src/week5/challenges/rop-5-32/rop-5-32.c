#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>


// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>

// for core dump
__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

char* strcpy(char *a, char *b) {
  while(*b) {
    *(a++) = *(b++);
  }
  *a = '\0';
  return a;
}

void null() {
#ifdef __x86_64__
  asm volatile("pop %rdx");
#endif
}


void input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  puts("Please type your name: ");
  read(0, buf, BUFSIZE*4);

  printf("Hello %s!\n", buf);
  return;
}

int main(int argc, char** argv, char** envp) {

  input_func();
  return 0;
}
