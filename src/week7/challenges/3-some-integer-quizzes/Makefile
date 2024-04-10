all: intquiz

intquiz: intquiz.c
	$(CC) -o $@ $< -z relro -z now -D_FORTIFY_SOURCE=2 -pie -fPIE -g

clean:
	rm -rf ./intquiz
