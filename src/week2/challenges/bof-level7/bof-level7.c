#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

char buffer[256];
int i;

void receive_input() {
    char buf[128];
    fgets(buffer, 256, stdin);
    for(i=0; i<=136; ++i) {
        buf[i] = buffer[i];
    }
}

int run() {
    printf("Now, the developer of this program is trained a bit more, however,\n");
    printf("still the vulnerability exists in th program: 1-byte overflow in the buffer,\n");
    printf("which is an off-by-one vulnerability!\n");
    printf("Can you exploit this program?\n");
    receive_input();
}

int main() {
    run();
}
