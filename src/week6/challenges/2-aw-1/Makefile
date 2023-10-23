all: aw-1

aw-1: aw-1.c
	cc -o $@ $< -m64 -fstack-protector -DBUFSIZE=128 -O0

clean:
	rm -rf aw-1
