all: one-format-string

one-format-string: one-format-string.c
	clang -o $@ $< -fstack-protector-strong -m64

clean:
	rm one-format-string
