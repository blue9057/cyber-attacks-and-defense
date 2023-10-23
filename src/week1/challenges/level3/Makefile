CC=clang

all: level3

level3: level3.c
	$(CC) -o $@ $< -fno-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE

clean:
	rm -rf level3
