CC=clang

all: bof-level3

bof-level3: bof-level3.c
	$(CC) -o $@ $< -fno-stack-protector -U_FORTIFY_SOURCE -O0

clean:
	rm -rf bof-level3
