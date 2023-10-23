CC=gcc

all: bof-level5

bof-level5: bof-level5.c
	$(CC) -o $@ $< -no-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level5
