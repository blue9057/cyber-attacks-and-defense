#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

int my_return_address = 0;
int new_return_address = 0;

void receive_input() {
    printf("I will store my return address to the global area first,\n"
            "and get the back the stored value to protect my stack!\n");

    asm volatile("mov 0x4(%%ebp), %0" :"=r"(my_return_address)::"memory");
    printf("my_return_address is %p\n", (void*)my_return_address);

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

    printf("Let's check the new return address\n");

    asm volatile("mov 0x4(%%ebp), %0" :"=r"(new_return_address)::"memory");

    printf("Previous ret addr %p, new ret addr %p\n",
        (void*)my_return_address, (void*)new_return_address);

    if(my_return_address != new_return_address) {
        printf("You have changed the return address, attack detected!\n");
        exit(-1);
    }
}

int main() {
    receive_input();
}
