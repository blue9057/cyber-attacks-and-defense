CC=clang

all: level5

level5: level5.c
	$(CC) -o $@ $< -fno-pie -m32 -fno-stack-protector -U_FORTIFY_SOURCE

clean:
	rm -rf level5
