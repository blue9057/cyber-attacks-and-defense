all: short-shellcode-64

CC=clang

short-shellcode-64: short-shellcode.c
	$(CC) -m64 -o short-shellcode-64 $< -z execstack

clean:
	@rm -rf short-shellcode-64
