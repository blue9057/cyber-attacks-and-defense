CC=clang

all: shellcode-32

shellcode-32: shellcode.c
	$(CC) -m32 -o $@ $<

clean:
	@rm -rf shellcode-32
