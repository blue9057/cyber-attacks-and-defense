all: sr-1

sr-1: sr-1.c
	cc -o $@ $< -m64 -fno-stack-protector -DBUFSIZE=128 -O0

clean:
	rm -rf sr-1
