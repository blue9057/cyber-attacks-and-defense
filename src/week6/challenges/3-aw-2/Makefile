all: aw-2

aw-2: aw-2.c
	cc -o $@ $< -m64 -fstack-protector -DBUFSIZE=128 -O0

clean:
	rm -rf aw-2
