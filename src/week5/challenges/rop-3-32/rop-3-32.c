#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#include <sys/prctl.h>
#include <sys/mman.h>

// for core dump
__attribute__((constructor))
static void set_dumpable() {
  prctl(PR_SET_DUMPABLE, 1);
}

void null_func() {
    // placeholder for a function
    mprotect(0, 0, 0);
#ifdef __x86_64__
  asm volatile("pop %rdx");
#endif
}

// global buffer..
char g_buf[1024];

void input_func() {
/*
 *  TASK: call mprotect to change permission of .data area
 *  (to Read-Write-eXecutable)
 *  and then jump to your shellcode.
 *
 *  mprotect(void *ptr, int size, int prot)
 *  can change permission of a memory page (see man mprotect).
 *
 *  How to call?
 *  1) Get the address of g_buf first. You can get that by running
 *     printf &g_buf in gdb.
 *
 *
 *  2) call mprotect(0x804a000, 0x1000, 7); // 7 is for Read, Write, and Exec.
 *     mprotect gets address argument aligned by a page boundary,
 *     so you should put 0x?????000. For example, if the target
 *     address that you would like to make that executable is
 *     0x804a541, then you should call mprotect for 0x804a000
 *     (size 0x1000 will make 0x804a000 ~ 0x804b000 be executable).
 *
 *
 *  So your job here is:
 *  1) put your shellcode on the buffer; will be copied into g_buf.
 *  2) run mprotect(addr_g_buf&0xfffff000, 0x1000, 7) via ROP
 *  3) jump to your shellcode (in g_buf).
 *
 *  It's easy:
 *  [A*xxx][saved EBP][mprotect][shellcode][0x804a???][0x1000]
 *
 *  Good luck!
 */


  // name buffer to overflow
  char buf[BUFSIZE];
  read(0, buf, 1024);
  memcpy(g_buf, buf, 1024);
  return;
}

int main(int argc, char** argv, char** envp) {

  volatile char buf[BUFSIZE*2];

  // change the current directory to /
  /* this is a symlink blocker. you can't create symlink at / */
  chdir("/");

  // disable PATH
  setenv("PATH", "", 1);

  input_func();
  return 0;
}
