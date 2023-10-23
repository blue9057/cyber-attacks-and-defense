all: stack-cookie-1

stack-cookie-1: stack-cookie-1.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=128 -O0

clean:
	rm -rf stack-cookie-1 stack-cookie-2 stack-cookie-3 stack-cookie-4
