#include <stdio.h>
#include <seccomp.h>
#include <stdlib.h>
#include <fcntl.h>

int good_luck = 0;

void
hint(void) {
    char buf[32];
    sprintf(buf, "/proc/%d/fd", getpid());
    if(fork() == 0) {
        printf("Here's a hint for you!\n");
        execl("/bin/ls", "ls", "-l", buf, NULL);
        // should never reach here!
        exit(-1);
    }
    else {
        waitpid(-1, NULL, 0);
        printf("Do you know how to hack this one?!\n");
    }
}

void
target(void) {
    char buf[32];
    printf("Here is a buffer overflow vulnerability for you!\n");
    read(0, buf, 512);
    printf("Hello %s!\n");
}

int main() {
    // just use open for checking the existence of the file.
    int fd = open("good luck", O_RDONLY);

    if (fd >= 0) {
        printf("Oh, you have a file named good luck! Wish you good luck!\n");
        printf("To see the hint correctly, please run './deprivileged-copy'\n");
        hint();
    }

    // deprivilege! Can you pwn this and read the flag?
    setregid(getgid(), getgid());
    printf("My gid is %d, my egid is %d!\n", getgid(), getegid());

    target();
}
