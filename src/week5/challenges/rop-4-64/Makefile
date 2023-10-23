all: rop-4-64


rop-4-64: rop-4-64.c
	cc -o $@ $< -m64 -fno-stack-protector -DBUFSIZE=128 -O0 -no-pie

clean:
	rm -rf rop-4-64
