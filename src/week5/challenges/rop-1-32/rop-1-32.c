#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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


// Executing some_function will do nothing for you ;)
int some_function() {
  setregid(-1, -1);
  execve(NULL, 0, 0);
}

void input_func() {
  // name buffer to overflow
  char buf[BUFSIZE];

  printf("Please call setregid(gid, gid);\n");
  printf("You can check the gid by running 'cat /etc/group'\n");
  printf("For example, the gid of week5-50000-ok is 50000\n");
  printf("And then call execve(\"/bin/sh\", 0, 0)\n");
  printf("Or you can use a symlink\n");
  printf("Please type your name: \n");
  read(0, buf, BUFSIZE * 2);

  printf("Hello %s!\n", buf);
  return;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
