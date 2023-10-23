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

int keys[512];
void number_generator() {
    int t = 2;
    int v;
    int p;
    keys[0] = 2;
    keys[1] = 3;

    for(v=4;t<500;v++) {
        for(p=0;p<t;++p) {
            int tv = keys[p];
            if(tv*tv > v) {
                keys[t] = v;
                t += 1;
                break;
            }
            if(v%tv == 0) {
                break;
            }
        }
        if(t == 500) break;
    }
}

int keys[] = { 3, 4 };

int check(int value) {
    for(int i=0; i<500; ++i) {
        if(value % keys[i] == 0) return 0;
    }
    return 1;
}

void password() {
    int answer;
    printf("Please send me the password.\n");
    scanf("%d", &answer);

    if(check(answer)) {
        printf("Great! you got my password!\n");
        get_a_shell();
    }
    else {
        printf("Uh oh, wrong value.\n");
    }
}

int main() {
    number_generator();
    printf("Let's start a game!\n");
    password();
}
