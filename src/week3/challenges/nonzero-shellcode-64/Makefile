CC=clang

all: nonzero-shellcode-64

nonzero-shellcode-64: shellcode.c
	$(CC) -m64 -o $@ $<

clean:
	@rm -rf nonzero-shellcode-64
