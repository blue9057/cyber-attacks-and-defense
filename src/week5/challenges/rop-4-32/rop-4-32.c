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
    open("a.txt", 0);
#ifdef __x86_64__
  asm volatile("pop %rdx");
#endif
}


void input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  printf("the quick brown fox jumps over the lazy dog!\n");
  printf("I also put this for you: 1234567890-\n");
  printf("Please type your name: \n");
  read(0, buf, 4096);

  printf("Hello %s!\n", buf);
  return;
}

int main(int argc, char** argv, char** envp) {

  volatile char buf[4096];

  // change the current directory to /
  chdir("/");

  // disable PATH
  setenv("PATH", "/bin:/usr/bin", 1);
  input_func();
  return 0;
}
