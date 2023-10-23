all: rop-5-32

rop-5-32: rop-5-32.c
	cc -o $@ $< -m32 -fno-stack-protector -DBUFSIZE=128 -O0 -no-pie

clean:
	rm -rf rop-5-32
