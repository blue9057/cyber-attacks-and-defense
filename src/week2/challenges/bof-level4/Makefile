CC=clang

all: bof-level4

bof-level4: bof-level4.c
	$(CC) -o $@ $< -m32 -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level4
