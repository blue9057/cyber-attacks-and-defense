#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include <unistd.h>

#include <sys/mman.h>

#define TRUE 1
#define FALSE 0

int is_numeric(char c) {
    if('0' <= c && c <= '9') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int is_alpha(char c) {
    if('a' <= c && c <= 'z') {
        return TRUE;
    }
    else if ('A' <= c && c <= 'Z') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int is_alphanumeric(char c) {
    if(is_alpha(c) || is_numeric(c)) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int is_ascii(char c) {
    unsigned char uc = (unsigned char)c;
    if('\0' <= uc && uc <= '\127') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void check_alphanumeric(char *ptr, size_t size) {
    for(int i=0; i<size; ++i) {
        if(!is_alphanumeric(ptr[i])) {
            printf("You have a non-alphanumeric character at position %d, char %d\n", \
                    i, ptr[i] & 0xff);
            exit(-1);
        }
    }
}

void check_ascii(char *ptr, size_t size) {
    for(int i=0; i<size; ++i) {
        if(!is_ascii(ptr[i])) {
            printf("You have a non-ascii character at position %d, char %d\n", \
                    i, ptr[i] & 0xff);
            exit(-1);
        }
    }
}

void check_non_zero(char *ptr, size_t size) {
    for(int i=0; i<size; ++i) {
        if(ptr[i] == '\0') {
            printf("You have a zero character at position %d, char %d\n", \
                    i, ptr[i] & 0xff);
            exit(-1);
        }
    }
}

int main() {
  void *ptr = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, \
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if(ptr == NULL) {
    printf("Map failed!\n");
    exit(-1);
  }
  printf("Reading shellcode from shellcode.bin\n");
  FILE *fp = fopen("shellcode.bin", "rb");
  if(fp == NULL) {
      printf("Failed to open shellcode.bin\n");
      exit(-1);
  }

  ssize_t read = fread(ptr, 1, 0x1000, fp);
  fclose(fp);
  if(read <= 0) {
    perror("File read");
    exit(-1);
  }

  ((void(*)())ptr)();
}
