
all: fs-arbt-write-32

fs-arbt-write-32: fs-arbt-write-32.c
	cc -o $@ $< -m32 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-arbt-write-32
