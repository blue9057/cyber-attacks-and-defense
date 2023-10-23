all: stack-ovfl-where-32

stack-ovfl-where-32: stack-ovfl-where.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=30

clean:
	rm -rf stack-ovfl-sc-32
