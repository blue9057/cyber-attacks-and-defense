
all: fs-arbt-read-32

fs-arbt-read-32: fs-arbt-read-32.c
	cc -o $@ $< -m32 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-arbt-read-32
