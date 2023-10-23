CC=clang

all: shellcode-64

shellcode-64: shellcode.c
	$(CC) -m64 -o $@ $<

clean:
	@rm -rf shellcode-64
