CC=clang

all: bof-level1

bof-level1: bof-level1.c
	$(CC) -o $@ $< -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level1
