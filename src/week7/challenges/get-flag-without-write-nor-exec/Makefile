all: get-flag-without-write-nor-exec

get-flag-without-write-nor-exec: get-flag-without-write-nor-exec.c
	clang -o $@ $< -fno-stack-protector -lseccomp

clean:
	rm get-flag-without-write-nor-exec
