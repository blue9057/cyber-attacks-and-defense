#include <stdio.h>

void target() {
    int i;
    printf("JUMP GAME\n");
    printf("Give me an address to jump. Then I will jump for you\n");
    scanf("%x", &i);
    printf("Your choice is: %p\n", (void*)i);
    // jump!
    ((void(*)(void))i)();
}

int main() {
    target();
}
