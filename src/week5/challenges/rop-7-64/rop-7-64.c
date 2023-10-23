#include <stdio.h>
#include <unistd.h>

#include <stdint.h>

// Please check the assembly for the correct buffer size
#ifndef BUFSIZE
#define BUFSIZE 128
#endif


int main(int argc, char** argv, char** envp) {
    uint64_t *ptr;
    read(0, &ptr, 8);
    ((int(*)(void))ptr)();
    return 0;
}
