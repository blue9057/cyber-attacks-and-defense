all: fs-no-binary-pie-64

fs-no-binary-pie-64: fs-no-binary-pie-64.c
	cc -o $@ $< -m64 -DBUFSIZE=128 -O0 -g -fPIE -pie

clean:
	rm -rf fs-no-binary-pie-64
