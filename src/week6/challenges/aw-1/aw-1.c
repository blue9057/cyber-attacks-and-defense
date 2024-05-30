#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

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


void please_execute_me() {
    setregid(getegid(), getegid());
    execve("/bin/sh", NULL, NULL);
}

int read_integer(char *format) {
  /* reads a string with new line and convert that to an integer */
  char buf[64];
  int ret;
  // no buffer overflow, 63 < 64!
  fgets(buf, 63, stdin);
  sscanf(buf, format, &ret);
  return ret;
}


volatile int i; // generate a crash for invalid address

void write_func() {

  /* primitives for arbitrary write; write N bytes from your input
   * to an address A */

  size_t read_size;
  int *ptr;

  puts("This function will read your input for N bytes and then write them to an address A.");

  // read N
  puts("How many bytes do you want to write (N, in decimal, max 128 bytes)?");
  read_size = read_integer("%lu");
  if(read_size > 128) {
    read_size = 128;
  }

  // read A
  puts("What is the address that you want to write (A, in hexadexmial, e.g., 0xffffde01)?");
  ptr = (int*) read_integer("%lx");

  // read your input (arbitrary write!)
  printf("Please provide your input (MAX %d bytes)\n", read_size);
  size_t read_bytes = read(0, ptr, read_size);

  // crash if ptr is an invalid pointer
  i = *ptr;

  printf("Writing %lu bytes to %p\n", read_bytes, ptr);

}


void input_func() {

  char buf[BUFSIZE];

  /* perform an arbitrary write */
  write_func();


  puts("Please type your name: ");
  /* no buffer overflow */
  read(0, buf, BUFSIZE-1);

  printf("Hello %s!\n", buf);

}

int main(int argc, char** argv, char** envp) {
  input_func();
  return 0;
}
