#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void
please_run_this(void) {
    setregid(getegid(), getegid());
    execve("/bin/sh", 0, 0);
}

int max_read_size = 63;

void target() {
    char buf[64];
    int *size = &max_read_size;
    printf("Please type your name: \n");
    read(0, buf, *size);
    buf[63] = '\0';
    // insecure
    printf(buf);

    printf("Please type your affiliation: \n");
    // HINT: can you overfill the buffer with this read?
    read(0, buf, *size);
    buf[63] = '\0';
    // secure
    printf("%s", buf);
}

int main() {
    target();
}
