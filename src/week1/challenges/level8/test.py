#!/usr/bin/env python

def fib(a, b, times):
    for i in xrange(times):
        t = b
        b = a+b
        a = t
    return b


def main():
    v = int(raw_input())
    print(fib(3,4,v))

if __name__ == '__main__':
    main()
