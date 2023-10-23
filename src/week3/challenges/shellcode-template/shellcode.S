#include <sys/syscall.h>

.globl  main
.type   main, @function

main:
  /*
      Objective:
        Calling three functions.

        int egid = getegid();
        setregid(egid, egid);
        execve("/bin/sh", 0, 0);
  */

  /*
    For 32 bit:

    Check the system call numbers at here:
    https://syscalls.kernelgrok.com/,
    and set showing entries to 100 to see them easier.

    // Syscall numbers
    $SYS_getegid == 50
    $SYS_setregid == 71
    $SYS_execve == 11

    // run syscall
    1. set %eax as the target system call number (e.g., for getegid, it's 50).
    2. set arguments to %ebx (1st), %ecx (2nd), %edx (3rd), %esi (4th), %edi (5)
    3. run 'int $0x80'  <-- an instruction that invokes interrupt 0x80,
        which is the system call activity in (x86/linux, 32bit)

    // building "//bin/sh" on the stack
    x86:
      push  $0                  // mark the end as 00 00 00 00 (4-byte zero)
      push  $0x68732f6e         // push 6e 2f 73 68  (n/sh)
      push  $0x69622f2f         // push 2f 2f 62 69  (//bi

                                // So, it is //bin/sh\0\0\0\0 -> "//bin/sh"

  */

  /*
    For 64bit:

    Check the system call numbers at here:
    http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

    $SYS_getegid == 108
    $SYS_setregid == 114
    $SYS_execve == 59

    // run syscall
    1. set %rax as the target system call number (e.g., for getegid, it's 108).
    2. set arguments to %rdi (1st), %rsi (2nd), %rdx (3rd), %rcx (4th), %r8 (5)
    3. run 'syscall'  <-- an instruction available in 64 bit...

    // building "//bin/sh" on the stack
    amd64:
      mov $0x68732f6e69622f2f, %rbx // rbx: //bin/sh
      push $0                       // mark the end as 00 00 00 00 00 00 00 00
      push %rbx                     // push //bin/sh
                                    // So, it is "//bin/sh"

  */


  // Please do the following tasks


  /*
    1. Call getegid().
    getegid() does not get any argument, and the result of the function
    will be stored into eax (or rax in 64bit) after calling of
    int $0x80 (or syscall in 64bit).
  */

  // WORK HERE:
  // set eax or rax to getegid()
  // call the system call.


  /*
    2. Call setregid(getguid(), getegid())
    The setregid(int, int) gets two arguments, and please set these
    arguments as the return value of getegid() call at step 1.

    For x86 (32bit), you need to set the ebx (1st) and ecx (2nd) registers
    for the arguments.

    For amd64 (64bit), you need to set rdi (1st) and rsi (2nd) registers
    for the arguments.
  */

  // WORK HERE:
  // Set arguments first.
  // call the system call.



  /*
    3. Call execve(const char* filename, char** argv, char** envp);
    The execve(const char*, char**, char**) gets three arguments.
    From the description of the function (from `man execve`),
    the call requires:

    1) The first argument to be a filepath of the target executable file,

    2) The second argument to be an argument vector (i.e., arguments of the
    program are listed as a list, and ends with zero, e.g., for running
    "ls -als /", the argument should point the address of an array
    that includes ["ls", "-als", "/", 0].

    If you set the entire list as NULL (set the argument as zero),
    this will be ignored, so I recommend you to use zero for
    the second argument (because it is easy. you do not have to build an array).

    3) The third argument to be an environment variables vector
    (i.e., variables that you can see if you type `env` in the console,
    variables are listed as a list, and ends with zero.
    E.g., for "A=1", "SHELL=bash", "TERM=xterm", the argument should point to
    the list ["A=1", "SHELL=bash", "TERM=xterm", 0].

    If you set the entire list as NULL (set the argument as zero),
    this will be ignored, so I recommend you to use zero for
    the third argument (because it is easy. you do not have to build an array).

    For x86, ebx (1st), ecx (2nd), and edx (3rd) are the registers for passing
    arguments.

    For amd64, rdi (1st), rsi (2nd), and rdx (3rd) are the registers for
    passing arugments.


    Your job is to run:
        setregid(getegid(), getegid());
        execve("//bin/sh", 0, 0);
  */

    // WORK HERE:
    // run ret = getegid()
    // run setregid(ret, ret);
    // build the "//bin/sh" string here.
    // set arguments.
    // call execve.
    // system call: 'int $0x80' in 32 bit, 'syscall' in 64 bit
