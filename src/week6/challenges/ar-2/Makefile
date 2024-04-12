all: ar-2

ar-2: ar-2.c
	cc -o $@ $< -m64 -fno-stack-protector -DBUFSIZE=128 -O0

clean:
	rm -rf ar-2
