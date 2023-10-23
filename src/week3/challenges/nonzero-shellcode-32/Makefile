CC=clang

all: nonzero-shellcode-32

nonzero-shellcode-32: shellcode.c
	$(CC) -m32 -o $@ $<

clean:
	@rm -rf nonzero-shellcode-32
