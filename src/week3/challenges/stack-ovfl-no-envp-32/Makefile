all: stack-ovfl-no-envp-32

stack-ovfl-no-envp-32: stack-ovfl-no-envp.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=4

clean:
	rm -rf stack-ovfl-no-envp-32
