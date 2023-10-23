#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

uint64_t result;

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void get() {
    result = 0;
    uint32_t value;
    for(int i=0; i<5; ++i) {
        printf("Please give me your integer %d\n", i+1);
        scanf("%u", &value);
        result += i * value;
    }
}
void calculate() {
    if(result == 0x11223344ul) {
        printf("Correct!\n");
        get_a_shell();
    }
    else {
        printf("Wrong value %llu!!\n", result);
    }
}


int main() {

    printf("Let's start a game of five integers!\n");
    printf("I do not let you know what I am doing internally!\n");
    get();
    calculate();
}
