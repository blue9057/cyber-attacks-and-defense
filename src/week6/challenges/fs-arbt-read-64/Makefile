
all: fs-arbt-read-64

fs-arbt-read-64: fs-arbt-read-64.c
	cc -o $@ $< -m64 -DBUFSIZE=128 -O0 -no-pie -g

clean:
	rm -rf fs-arbt-read-64
