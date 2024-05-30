#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

char command[256];
char user_args[64];

char *bad_characters = "./;|&`";

void
check_input(char *user_input) {
    int len = strlen(user_input);
    int len2 = strlen(bad_characters);
    for (int i=0; i<len; ++i) {
        for(int j=0; j<len2; ++j) {
            if (user_args[i] == bad_characters[j]) {
                printf("You have a bad character %c at position %d\n", bad_characters[j], i);
                exit(-1);
            }
        }
    }
}

int main() {
    setenv("PATH", "/bin", 1);
    printf("THIS IS A SECURE LS MACHINE\n");
    printf("Which directory do you want to take a look at?\n");
    scanf("%50s", user_args);
    check_input(user_args);
    snprintf(command, 256, "ls -l %s", user_args);
    setregid(getegid(), getegid());
    system(command);
}
