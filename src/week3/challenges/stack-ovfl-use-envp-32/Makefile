all: stack-ovfl-use-envp-32

stack-ovfl-use-envp-32: stack-ovfl-use-envp.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=4

clean:
	rm -rf stack-ovfl-use-envp
