CC=gcc

all: bof-level8

bof-level8: bof-level8.c
	$(CC) -o $@ $< -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level8
