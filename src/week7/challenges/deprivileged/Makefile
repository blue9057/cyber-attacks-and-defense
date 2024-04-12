all: deprivileged

deprivileged: deprivileged.c
	gcc -o $@ $< -fno-stack-protector -no-pie

clean:
	rm deprivileged
