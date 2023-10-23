all: stack-cookie-2

stack-cookie-2: stack-cookie-2.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=128 -O0

clean:
	rm -rf stack-cookie-2
