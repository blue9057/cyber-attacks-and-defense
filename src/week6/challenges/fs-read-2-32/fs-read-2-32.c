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

struct variable {
  int other;
  char name[64];
  // Argggh.. this buffer is too long
  char buf[512];
  int random;
  /*
   * On the stack, these variables will be placed in backward:
   * [ret addr]
   * [saved ebp]            <-- %ebp points here
   * [other...]
   * [random - 4 bytes]
   * [name - 64 bytes]
   * [buf - 512 bytes]
   * [other - 4 bytes]
   * [arg space]
   * [arg space]
   * [arg space]            <-- %esp points here...
   *
   * check the disassembly to get a more accurate information
   */
};


int input_func() {

  struct variable var;

  printf("Please type your name first: \n");
  // only reads 63 chars at max
  read(0, var.name, 63);
  var.random = read_random();
  printf("Hello ");

  // Format String Vulnerability here
  printf(var.name);

  printf("\n");
  printf("Can you guess the random?\n");
  scanf("%x", &var.other);
  if(var.other == var.random) {
    printf("Great!\n");
    setregid(getegid(), getegid());
    system("/bin/bash");
  }
  else {
    printf("Wrong, your random was 0x%08x but you typed 0x%08x\n",
        var.random, var.other);
    exit(-1);
  }
  return 0;
}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
