#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}


// function placeholder
int some_function() {
  open("", 0);
  read(0, "", 1);
  write(0, "", 1);

  // a free gadget for you.
  asm volatile("pop %rdx; ret");
}

void input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  write(1, "Please type your name: \n", 24);
  read(0, buf, BUFSIZE * 3);

  printf("Hello %s!\n", buf);
  return;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
