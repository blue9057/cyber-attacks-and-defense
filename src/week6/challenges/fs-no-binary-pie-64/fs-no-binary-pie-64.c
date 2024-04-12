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

void
call_many_functions() {
    puts("");
    open("", 0, 0);
    read(0, "", 0);
    write(1, "", 0);
    chdir("");
    getpid();
    getppid();
    fopen("", "");
    fclose(0);
    fread(NULL, 0, 0, 0);
    fwrite(NULL, 0, 0, 0);
}

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

  setregid("asdf", 0);
  chdir("ASDF");
  write(1, "No binary, it does not make any sense!\n", 39);

  return 0;
}

int main(int argc, char** argv, char** envp) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  input_func();
  return 0;
}
