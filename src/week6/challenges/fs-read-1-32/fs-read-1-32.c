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


// Get a random value from a secure source
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

int input_func() {

  char name[64];

  // read random here
  int random = read_random();

  int other = 0;

  printf("Please type your name first: \n");
  // only reads 63 chars at max; no buffer overflow.
  read(0, name, 63);

  printf("Hello ");
  // A Format String vulnerability here
  printf(name);
  printf("\n");

  printf("Can you guess the random?\n");
  scanf("%x", &other);

  // You must guess and match the random!
  if(other == random) {
    printf("Great!\n");
    setregid(getegid(), getegid());
    system("/bin/bash");
  }
  else {
    printf("Wrong, your random was 0x%08x but you typed 0x%08x\n",
        random, other);
    exit(-1);
  }
  return 0;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
