CC=clang

all: level8

level8: level8.c
	$(CC) -o $@ $< -fno-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE

clean:
	rm -rf level8
