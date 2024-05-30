#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>

#define N_QUIZZES (1)

void *quizzes[100];

int global_counter = 0;

void
seed_random(void) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        printf("Failed to get random\n");
        exit(-1);
    }
    int rv = 0;
    read(fd, &rv, sizeof(int));
    if (rv == 0) {
        printf("Failed to get random\n");
        exit(-1);
    }
    close(fd);
    srand(rv);
}

int
get_input(int limit) {
    int i = -1;
    char buf[50];
    int ret = 0;
    while (1) {
        scanf("%40s", buf);
        i = atoi(buf);
        if (i < 0 || i > limit || buf[0] < '0' || buf[0] > '9') {
            printf("Wrong number value, type a number from 0 to %d!\n", limit);
            ret = 0;
            continue;
        }
        else {
            break;
        }
    }
    return i;
}

void
shuffle(char **choices, int *answers, int length) {
    int max = rand() % 100 + 20;
    printf("Shuffling %d times\n", max);
    for (int i=0; i<max; ++i) {
        int t1 = rand() % length;
        int t2 = t1;
        while (t1 == t2) {
            t2 = rand() % length;
        }
        char **tc;
        int *ti;
        tc = choices[t1];
        ti = answers[t1];
        choices[t1] = choices[t2];
        answers[t1] = answers[t2];
        choices[t2] = tc;
        answers[t2] = ti;
    }
}

void
quiz0(void) {
    char *choices[2] = {"True", "False"};
    int answers[2] = {0, 1};
    shuffle(choices, answers, 2);

    printf("Q %d: uint32_t a = 0, b = 1; --a; is a < b? \n", global_counter);
    for (int i=0; i<2; ++i) {
        printf("%d. %s\t", i, choices[i]);
    }
    printf("\n");
    printf("Your answer?\n");
    //printf("Answer %d %d\n", answers[0], answers[1]);
    int input = get_input(1);
    if (answers[input] == 1) {
        printf("Great!\n");
    }
    else {
        printf("Wrong\n");
        exit(-1);
    }
}

void
quiz1(void) {
    char *choices[5] = {"0 on both platforms", "1 on both platforms", "0 on amd64, 1 on x86", "1 on amd64, 0 on x86"};
    int answers[5] = {0, 1};
    shuffle(choices, answers, 2);

    printf("Q %d: -1l > 1u? on x86 and amd64 \n", global_counter);
    for (int i=0; i<2; ++i) {
        printf("%d. %s\t", i, choices[i]);
    }
    printf("\n");
    printf("Your answer?\n");
    //printf("Answer %d %d\n", answers[0], answers[1]);
    int input = get_input(1);
    if (answers[input] == 1) {
        printf("Great!\n");
    }
    else {
        printf("Wrong\n");
        exit(-1);
    }
}

int main() {
    seed_random();
    quizzes[0] = quiz0;
    //quizzes[0] = quiz0;
    //quizzes[0] = quiz0;
    //quizzes[0] = quiz0;
    //quizzes[0] = quiz0;
    //quizzes[0] = quiz0;
    printf("Welcome to Integer Quizzes!\n");
    for (int i=0; i<N_QUIZZES; ++i) {
        int roll = rand() % N_QUIZZES;
        while (quizzes[roll] == NULL) {
            roll = rand() % N_QUIZZES;
        }
        ((void(*)())quizzes[roll])();
        global_counter +=1;
        quizzes[roll] = 0;
    }

    system("cat flag");
}
