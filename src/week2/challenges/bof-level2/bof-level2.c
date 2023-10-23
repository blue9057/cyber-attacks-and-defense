#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void receive_input() {
    int a = 0x41414141, b = 0x42424242;
    char buf[20];

    printf("Values in two local variables are:\n"
            "a = 0x%08x and b = 0x%08x\n", a, b);

    printf("Can you change these values to:\n"
            "a = 0x48474645 and b = 0x44434241?\n");

    printf("Type YES if you agree with this... "
            "(a fake message, you may overflow the input buffer).\n");
    fgets(buf, 128, stdin);

    printf("Now the variables store:\n"
            "a = 0x%08x b = 0x%08x\n", a, b);

    if(a == 0x48474645 && b == 0x44434241) {
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
