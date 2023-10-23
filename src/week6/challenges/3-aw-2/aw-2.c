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

int read_integer(char *format) {
  /* reads a string with new line and convert that to an integer */
  char buf[64];
  int ret;
  // no buffer overflow, 63 < 64!
  fgets(buf, 63, stdin);
  sscanf(buf, format, &ret);
  return ret;
}

void read_func() {

  /* primitives for arbitrary read; read N bytes from an address A */

  size_t read_size;
  void *ptr;

  puts("This function will read N bytes from address A and print them");

  // read N
  puts("How many bytes do you want to read (N, in decimal)?");
  read_size = read_integer("%lu");

  // read A
  puts("What is the address that you want to read (A, in hexadexmial, e.g., 0xffffde01)?");
  ptr = (void*)read_integer("%lx");

  // arbitrary read
  printf("Reading %lu bytes from %p\n", read_size, ptr);
  fwrite(ptr, 1, read_size, stdout);
  fflush(stdout);
  return;
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
  printf("Please provide your input (MAX %d bytes)", read_size);
  size_t read_bytes = read(0, ptr, read_size);

  // crash if ptr is an invalid pointer
  i = *ptr;

  printf("Writing %lu bytes to %p\n", read_bytes, ptr);

}


void input_func() {

  /* perform arbitrary read first */
  read_func();

  /* then do arbitrary write */
  write_func();

}

int main(int argc, char** argv, char** envp) {
  /* setregid for you */
  setregid(getegid(), getegid());
  input_func();
  return 0;
}
