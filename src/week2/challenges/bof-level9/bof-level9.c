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
    char buf[120];
    printf("Now we have a buffer overflow vulnerability,\nh");
    printf("but the vulnerability cannot reach to the return address...\n");
    printf("Can you exploit this program?\n");
    fgets(buf, 192, stdin);
}
