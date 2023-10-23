#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void receive_input() {
    uint64_t a = 0x4141414141414141, b = 0x4242424242424242;
    char buf[20];

    printf("This is a 64-bit program.\n");
    printf("The 1st argument will be passed via rdi, the 2nd will be passed via rsi,\nthe 3rd will be passed via rdx, the 4th will be pased via rcx, etc..\n");
    printf("Values in two local variables are:\n"
            "a = 0x%016lx b = 0x%016lx\n", a, b);

    printf("Can you change these values to:\n"
            "a = 0x6867666564636261 and b = 0x4847464544434241?\n");

    printf("Type YES if you agree with this... (a fake message, you may overflow the input buffer).\n");
    fgets(buf, 128, stdin);
    printf("Now the variables store:\n"
            "a = 0x%016lx b = 0x%016lx\n", a, b);

    if(a == 0x6867666564636261 && b == 0x4847464544434241) {
        printf("Great, but I will not execute get_a_shell() for you..\n");
        printf("Run it yourself!\n");
    }
    else {
        printf("Analyze the program!\n");
        exit(-1);
    }
}

int main() {
    receive_input();
}
