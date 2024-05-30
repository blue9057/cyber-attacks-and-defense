#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int
main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    char filename[512];
    char buf[512];
    printf("Get some caffeine\n");
    sleep(1);
    printf("Get some caffeine.\n");
    sleep(1);
    printf("Get some caffeine..\n");

    printf("Welcome to Secure File Reader!\n");
    printf("Hint: Exploit Time-of-check-to-time-of-use (TOCTTOU) bug!\n");
    printf("Type the name of file that you would like to open!\n");
    fgets(filename, 100, stdin);

    for (int i=0; i<100; ++i) {
        if (filename[i] == '\n')
            filename[i] = '\0';
    }

    // time of check
    printf("Stat of the file:\n");
    struct stat s;
    int ret = stat(filename, &s);
    if (ret != 0) {
        printf("Stat failed, please put the name of real file!\n");
        exit(-1);
    }
    printf("My gid is %d, the file is with the group id %d!\n", getgid(), s.st_gid);
    if (getgid() != s.st_gid) {
        printf("You cannot read the file that is not with your group id!\n");
        exit(-1);
    }

    /*  No sleep with high-caffeine dose
    printf("Processing\n");
    sleep(1);
    printf("Processing.\n");
    sleep(1);
    printf("Processing..\n");
    sleep(1);
    */

    // time of use, use twice due to caffeine jitter!
    int fd;
    fd = open(filename, O_RDONLY);

    memset(buf, 0, sizeof(buf));
    printf("Reading the file!!!\n");

    // Hint: make this read blocked by named pipe
    read(fd, buf, 100);
    write(1, buf, 100);
    close(fd);
    printf("Finished, UwU!\n");

    fd = open(filename, O_RDONLY);

    memset(buf, 0, sizeof(buf));
    printf("Reading the file!!!\n");
    // Hint: read the flag from this read
    read(fd, buf, 100);
    write(1, buf, 100);
    close(fd);
    printf("Finished, UwU!\n");


}
