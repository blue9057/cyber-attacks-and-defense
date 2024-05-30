all: fs-code-exec-32

fs-code-exec-32: fs-code-exec-32.c
	cc -o $@ $< -m32 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-code-exec-32
