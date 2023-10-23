#include <stdio.h>
#include <stdint.h>
#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}


int keys[] = { 1, 720, 24, 2, 1, 6, 120 };

void password() {
    int i, j, a, b;
    int mykeys[8];
    printf("Send me 7 lucky integers\n");

    for(i=0; i<7; ++i) {
        printf("Integer %d: ", i+1);
        scanf("%d", &mykeys[i]);
        printf("Integer %d is %d\n", i+1, mykeys[i]);
    }

    j = keys[i];
    for(i=0; i<7; ++i) {
        for(j=0; j<6; ++j) {
            a = keys[j];
            b = keys[j+1];
            if(a>b) {
                keys[j] = b;
                keys[j+1] = a;
            }
        }
    }

    for(i=0; i<7; ++i) {
        if(keys[i] != mykeys[i]) {
            printf("Oh no that's not the key\n");
            return;
        }
    }

    printf("Great! you got my password!\n");
    get_a_shell();
    return;
}

int main() {
    printf("Let's start an esoteric game!\n");
    password();
}
