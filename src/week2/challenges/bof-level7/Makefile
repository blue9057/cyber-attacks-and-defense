CC=gcc

all: bof-level7

bof-level7: bof-level7.c
	$(CC) -o $@ $< -no-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level7
