all: stack-ovfl-no-envp-no-argv-32

stack-ovfl-no-envp-no-argv-32: stack-ovfl-no-envp-no-argv.c
	cc -o $@ $< -m32 -fno-stack-protector -z execstack -DBUFSIZE=4

clean:
	rm -rf stack-ovfl-no-envp-no-argv-32
