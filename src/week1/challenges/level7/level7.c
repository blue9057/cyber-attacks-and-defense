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

void add_a_space(char *string) {
    int i=0;
    while(string[i] != '\0') {
        string[i] = (string[i] + 0x20) & 0xff;
        i += 1;
    }
}

void password() {

    char buf[512];

    memset(buf, 0, 512);

    scanf("%50s", buf);
    printf("Your buffer: %s\n", buf);

    int length = strlen(buf);

    memfrob(buf, length);
    add_a_space(buf);

    uint32_t value = atoi(buf);

    printf("Your Integer: %u\n", value);
    snprintf(buf, 20, "%x", value);
    printf("Your Hex Integer: %s\n", buf);

    length = strlen(buf);

    memfrob(buf, length);
    add_a_space(buf);

    if(memcmp(buf, ">:3hhn<", 4) == 0) {
        printf("Great! you got my password!\n");
        get_a_shell();
        return;
    }
    else {
        printf("Oh no\n");
    }
}

int main() {
    printf("Let's start an esoteric game!\n");
    password();
}
