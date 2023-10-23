#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

int main() {

    int value = 0;
    printf("What's the password?\n");
    scanf("%d", &value);
    if(value == 1457664) {
        printf("Correct!\n");
        get_a_shell();
    }
    else {
        printf("Wrong password!!\n");
    }

}
