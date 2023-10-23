all: dep-1

dep-1: dep-1.c
	cc -o $@ $< -m32 -fno-stack-protector -DBUFSIZE=128 -O0

clean:
	rm -rf dep-1 dep-2 dep-3
