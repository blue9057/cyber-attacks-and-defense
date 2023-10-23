all: rop-1-32

rop-1-32: rop-1-32.c
	cc -o $@ $< -m32 -fno-stack-protector -DBUFSIZE=128 -O0 -no-pie

clean:
	rm -rf rop-1-32 rop-2-64 rop-3-32 rop-4-64
