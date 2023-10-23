all: ascii-shellcode-64
CC=clang
ascii-shellcode-64: ascii-shellcode.c
	$(CC) -o $@ $< -m64

clean:
	rm -rf ascii-shellcode-64
