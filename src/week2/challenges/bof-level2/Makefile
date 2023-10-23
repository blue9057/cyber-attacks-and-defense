CC=clang

all: bof-level2

bof-level2: bof-level2.c
	$(CC) -o $@ $< -m32 -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level2
