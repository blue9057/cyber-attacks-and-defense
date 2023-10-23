all: fs-read-2-64

fs-read-2-64: fs-read-2.c
	cc -o $@ $< -m64 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-read-2-64
