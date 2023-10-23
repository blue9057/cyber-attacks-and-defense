all: 2048

2048: 2048.c
	$(CC) -std=gnu99 -O0 -I../../shared -fPIE -pie -Wl,-z,relro,-z,now -fstack-protector-all -o $@ $<

clean:
	rm -rf 2048
