all: short-shellcode-32

CC=clang

short-shellcode-32: short-shellcode.c
	$(CC) -m32 -o short-shellcode-32 $< -z execstack

clean:
	@rm -rf short-shellcode-32
