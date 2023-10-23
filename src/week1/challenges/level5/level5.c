#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

uint64_t result;

char password_string[] = "5385876380";

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void password() {
    char buf[512];
    memset(buf, 0, 512);

    // manual scanf
    int t;
    char *a;
    for(int i=0; i<sizeof(buf); ++i) {
        a = (char*)&t;
        read(0, a, 1);
        if(*a == '\n') {
            buf[i] = '\0';
            break;
        }
        else {
            buf[i] = *a;
        }
    }


    // manual strlen
    int length;
    for(int i=0; i<sizeof(buf); ++i) {
        if(buf[i] == '\0') {
            length = i;
            break;
        }
    }

    if(length != 7) {
        printf("Wrong string length!\n");
        exit(-1);
    }

    // use atoi insteads
    uint32_t value = atoi(buf);
    snprintf(buf, 20, "%u", value);


    // manual xor-ring.
    for(int i=0; i<10; ++i) {
        if((buf[i] ^ 0x1) != password_string[i]) {
            printf("Wrong password, access denied.\n");
            exit(-1);
        }
    }

    printf("Great! you got my password!\n");
    get_a_shell();
    return;
}

int main() {
    printf("Let's start a more complex game!\n");
    password();
}
