all: rop-4-32

rop-4-32: rop-4-32.c
	cc -o $@ $< -m32 -fno-stack-protector -DBUFSIZE=128 -O0 -no-pie

clean:
	rm -rf rop-4-32
