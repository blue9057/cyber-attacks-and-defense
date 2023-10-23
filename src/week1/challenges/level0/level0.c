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
    char buf[512];
    printf("What's the password?\n");
    scanf("%s", buf);
    if(strcmp(buf, "PaSSw0Rd") == 0) {
        printf("Correct!\n");
        get_a_shell();
    }
    else {
        printf("Wrong password!!\n");
    }
}
