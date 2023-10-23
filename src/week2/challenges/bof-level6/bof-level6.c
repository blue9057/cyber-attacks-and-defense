#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

void get_a_shell() {
    printf("Spawning a privileged shell\n");
    setregid(getegid(), getegid());
    execl("/bin/bash", "bash", NULL);
}

void receive_input() {
    char buf[128];
    read(0, buf, 136);
}

int run() {
    char buf[128];
    printf("Now the program contains a buffer overflow vulnerability,\n");
    printf("but the vulnerability does not allow us to overwrite the return address...\n");
    printf("Can you exploit this program?\n");
    receive_input();
}

int main() {
    run();
}
