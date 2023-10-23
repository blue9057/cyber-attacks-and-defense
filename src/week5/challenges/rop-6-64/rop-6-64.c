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

void null_func() {
    execve("", 0, 0);
}


void input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];
  write(1, "Please type your name: \n", 25);
  read(0, buf, 4096);

  return;
}

int main(int argc, char** argv, char** envp) {
  char dummy_buffer[4096];
  input_func();
  return 0;
}
