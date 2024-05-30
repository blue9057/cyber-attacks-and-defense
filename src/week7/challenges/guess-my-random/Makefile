all: guess-my-random

guess-my-random: guess-my-random.c
	gcc -o $@ $< -fno-stack-protector -m32

clean:
	rm guess-my-random
