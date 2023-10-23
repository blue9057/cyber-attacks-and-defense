all: rop-2-64

rop-2-64: rop-2-64.c
	cc -o $@ $< -m64 -DBUFSIZE=128 -O0 -fno-stack-protector -no-pie


clean:
	rm -rf rop-1-32 rop-2-64 rop-3-32 rop-4-64
