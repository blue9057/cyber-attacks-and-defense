all: fs-code-exec-64

fs-code-exec-64: fs-code-exec-64.c
	cc -o $@ $< -m64 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-code-exec-64
