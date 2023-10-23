#include <stdio.h>
#include <stdint.h>
#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}


int keys[] = { 3, 4 };

void password() {
    printf("THREE FOUR MACHINES\n");
    int value = rand() % 20 + 15;
    int answer;

    printf("I will use %d for my lucky number.\n", value);
    printf("Please send me your lucky number.\n");
    scanf("%d", &answer);

    for(int i=0; i<value; ++i) {
        int t = keys[1];
        keys[1] = keys[0] + keys[1];
        keys[0] = t;
    }

    if(keys[1] == answer) {
        printf("Great! you got my password!\n");
        get_a_shell();
    }
    else {
        printf("Uh oh, wrong value.\n");
    }
}

int main() {
    printf("Let's start a THREE FOUR game!\n");
    srand(time(0));
    password();
}
