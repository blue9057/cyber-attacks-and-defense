all: stack-ovfl-sc-32

CC=clang

stack-ovfl-sc-32: stack-ovfl-sc.c
	$(CC) -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=128

stack-ovfl-sc-64: stack-ovfl-sc.c
	$(CC) -o $@ $< -m64 -fno-stack-protector -z execstack -DBUFSIZE=128

clean:
	rm -rf stack-ovfl-sc-32 stack-ovfl-sc-64
