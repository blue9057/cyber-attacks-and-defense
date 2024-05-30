#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PASSWD "sW33tC4ndYiSf0rcAND"

int main(int argc, char** argv) {
    char buf[512];
    memset(buf, 0, 512);
    alarm(10);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    char *cur = PASSWD;
    char *end = PASSWD + strlen(PASSWD);

    /* mimic ubuntu */
    printf("Ubuntu 18.04 bionic-beaver tty1\n");
    printf("ubuntu login: root\n");
    printf("password: ");

    for (; cur < end; cur ++) {
        int c = fgetc(stdin);
        if (c == '\n')
            break;
        /* short circuit */
        if (*cur != c) {
            break;
        }
        /* HINT: this makes the challenge easy */
        usleep(20000);
    }

    if (cur == end) {
        int fd = open("flag", O_RDONLY);
        read(fd, buf, 100);
        printf("%s\n", buf);
    } else {
        printf("Incorrect password!\n");
    }

    return 0;
}
