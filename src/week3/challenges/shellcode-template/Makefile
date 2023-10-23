all:
	@echo "Please run either 'make 32' or 'make 64'"

32: shellcode.S
	gcc -m32 -c -o shellcode.o $< &&\
	gcc -o shellcode shellcode.o -m32 && \
	objcopy -S -O binary -j .text shellcode.o shellcode.bin

64: shellcode.S
	gcc -m64 -c -o shellcode.o $< &&\
	gcc -o shellcode shellcode.o -m64 && \
	objcopy -S -O binary -j .text shellcode.o shellcode.bin

objdump:
	@objdump -d shellcode.o

print:
	@python -c "import sys; print repr(sys.stdin.read())" < shellcode.bin

dump:
	@xxd shellcode.bin

run:
	./shellcode

clean:
	@rm -rf shellcode shellcode.o shellcode.bin
