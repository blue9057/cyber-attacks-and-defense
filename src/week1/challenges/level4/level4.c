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
    uint32_t value[5];
    for(int i=0; i<5; ++i) {
        printf("Please give me your integer %d\n", i+1);
        scanf("%u", &value[i]);
    }

    result += value[0] + value[3] + value[4];
}
void calculate() {
    if(result == 1213952) {
        printf("Correct!\n");
        get_a_shell();
    }
    else {
        printf("Wrong value %llu!!\n", result);
        exit(-1);
    }
}

void password() {
    char buf[512];
    memset(buf, 0, 512);
    scanf("%20s", buf);

    size_t length = strlen(buf);
    if(length != 16) {
        printf("Wrong string length!\n");
        exit(-1);
    }

    uint32_t value = strtoul(buf, 0, 10);
    snprintf(buf, 20, "%d", value);

    if(strcmp(buf, "13371337") == 0) {
        result = value;
        printf("Great! you got my password!\n");
        return;
    }
    else {
        printf("Wrong password, access denied.\n");
        exit(-1);
    }

    // not-reach
    exit(-2);
}

int main() {
    printf("Let's start a more complex game!\n");
    password();
    get();
    calculate();
}
