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


// Random value as a global variable (.bss)
int random_value;

void read_random() {
  int fd = open("/dev/urandom", O_RDONLY);
  if(fd < 0) {
    printf("Error on opening random\n");
    exit(-1);
  }
  // directly read it to .bss. No trace on the stack!
  read(fd, &random_value, 4);
  close(fd);
}

int input_func() {
  int other = 0;
  char name[64];
  printf("Please type your name first: \n");
  // only reads 63 chars at max
  read(0, name, 63);
  printf("Hello ");

  // Format String Vulnerability here
  printf(name);


  printf("\n");
  printf("Can you guess the random?\n");
  scanf("%x", &other);

  // Ah, random is not on the stack. How come???????
  if(other == random_value) {
    printf("Great!\n");
    setregid(getegid(), getegid());
    system("/bin/bash");
  }
  else {
    printf("Wrong, your random was 0x%08x but you typed 0x%08x\n",
        random_value, other);
    exit(-1);
  }
  return 0;
}

int main(int argc, char** argv, char** envp) {
  read_random();
  input_func();
  return 0;
}
