CC=gcc

all: bof-level6

bof-level6: bof-level6.c
	$(CC) -o $@ $< -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level6
