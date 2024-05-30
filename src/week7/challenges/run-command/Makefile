all: run-command

run-command: run-command.c
	gcc -o $@ $< -fno-stack-protector -m64

clean:
	rm run-command
