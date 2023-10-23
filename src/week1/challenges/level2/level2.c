#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

uint64_t result;
uint32_t value1, value2, value3;

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void get1() {
    printf("Input for X:\n");
    scanf("%u", &value1);
}
void get2() {
    printf("Input for Y:\n");
    scanf("%u", &value2);
}
void get3() {
    printf("Input for Z:\n");
    scanf("%u", &value3);
}

void calculate() {
    result = value3 * value2 + value1;
    if(result == 0x444e4143ul) {
        printf("Correct!\n");
        get_a_shell();
    }
    else {
        printf("Wrong value %llu!!\n", result);
    }
}


int main() {
    result = value1 = value2 = value3 = 0;

    printf("Let's start a game of three integers!\n");
    printf("We will do a simple calculation: X # Y ? Z = W,\n" \
           "where X, Y, Z, and W are uint32_t values, and # and ? are\n" \
           "some operators...\n");
    printf("Your job is to get the operators, and match your X, Y, and Z\n" \
           "values to W after applying all operators...\n");
    get1();
    get2();
    get3();

    calculate();
}
