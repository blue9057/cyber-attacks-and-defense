CC=clang

all: level4

level4: level4.c
	$(CC) -o $@ $< -fno-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE

clean:
	rm -rf level4
