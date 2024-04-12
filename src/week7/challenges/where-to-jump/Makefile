all: where-to-jump

where-to-jump: where-to-jump.c
	clang -o $@ $< -fstack-protector-strong -m32

clean:
	rm where-to-jump
