all: dep-3

dep-3: dep-3.c
	cc -o $@ $< -m32 -DBUFSIZE=128 -O0 -static -fno-stack-protector

clean:
	rm -rf dep-1 dep-2 dep-3
