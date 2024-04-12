#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>

__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

int read_random() {
  int fd = open("/dev/urandom", O_RDONLY);
  int ret;
  if(fd < 0) {
    printf("Error on opening random\n");
    exit(-1);
  }
  read(fd, &ret, 4);
  return ret;
}

int global_random = 0;

int input_func() {
  // global
  global_random = read_random();

  char name[64];
  printf("Please type your name first: \n");
  // only reads 63 chars at max
  read(0, name, 63);
  printf("Hello ");
  printf(name);
  printf("\n");

  if(global_random == 0xfaceb00c) {
    printf("Great!\n");
    setregid(getegid(), getegid());
    system("/bin/bash");
  }
  else {
    printf("Wrong, your global_random is 0x%08x "
        "but I wish it to be: 0x%08x\n",
        global_random, 0xfaceb00c);
    exit(-1);
  }
  return 0;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
