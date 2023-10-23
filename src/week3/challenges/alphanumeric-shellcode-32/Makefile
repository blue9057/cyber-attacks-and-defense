all: alphanumeric-shellcode
CC=clang
alphanumeric-shellcode: alphanumeric-shellcode.c
	$(CC) -o $@-32 $< -m32

clean:
	rm -rf alphanumeric-shellcode-32
