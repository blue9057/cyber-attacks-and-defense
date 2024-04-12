#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE 64

void
please_run_this(void) {
    setregid(getegid(), getegid());
    execve("/bin/sh", 0, 0);
}

char RANDOM_STRING[MAX_BUFFER_SIZE];

void
read_random(void) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        printf("Error, can't open /dev/urandom\n");
        exit(-1);
    }
    uint32_t random_int = 0;
    read(fd, &random_int, sizeof(uint32_t));
    close(fd);
    if (random_int == 0) {
        printf("Error, random read failed\n");
        exit(-1);
    }
    sprintf(RANDOM_STRING, "RANDVAL==%p\n", (void*)random_int);
    target();
}

int max_read_size = 63;

void target() {
    printf("Please guess my random!\n");
    printf("Please type a hexadecimal number!\n");

    char string[MAX_BUFFER_SIZE];
    char buf[MAX_BUFFER_SIZE];

    fgets(buf, MAX_BUFFER_SIZE, stdin);
    sprintf(string, "RANDVAL==%s", buf);

    if (strcmp(string, RANDOM_STRING) == 0) {
        printf("Great!\n");
        please_run_this();
    }
    else {
        printf("Wrong guess! My secret random was %s", RANDOM_STRING);
    }
}

int main() {
    read_random();
}
