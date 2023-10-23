CC=gcc

all: bof-level9

bof-level9: bof-level9.c
	$(CC) -o $@ $< -no-pie -fno-stack-protector -U_FORTIFY_SOURCE -O0 -m32

clean:
	rm -rf bof-level9
