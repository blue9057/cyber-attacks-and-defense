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

  char name[1024];
  printf("Please type your name first: \n");
  // only reads 1023 chars at max
  read(0, name, 1023);
  printf("Hello ");
  printf(name);
  printf("\n");

  printf("Please type your affiliation: \n");
  // only reads 1023 chars at max
  read(0, name, 1023);
  printf("You are from: ");
  printf(name);
  printf("\n");

  printf("Please leave a note: \n");
  // only reads 1023 chars at max
  read(0, name, 1023);
  printf("Your note is: ");
  printf(name);
  printf("\n");

  puts("Thank you!");

  return 0;
}

int main(int argc, char** argv, char** envp) {
  // Inherit EGID here..
  setregid(getegid(), getegid());
  input_func();
  return 0;
}
