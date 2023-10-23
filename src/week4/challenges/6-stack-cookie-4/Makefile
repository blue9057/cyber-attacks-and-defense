all: stack-cookie-4

stack-cookie-4: stack-cookie-4.c
	cc -o $@ $< -m32 -z execstack -DBUFSIZE=128 -O0 -fstack-protector

clean:
	rm -rf stack-cookie-1 stack-cookie-2 stack-cookie-3 stack-cookie-4
