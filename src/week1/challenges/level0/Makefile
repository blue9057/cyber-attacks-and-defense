CC=clang

all: level0

level0: level0.c
	$(CC) -o $@ $< -fno-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE

clean:
	rm -rf level0
