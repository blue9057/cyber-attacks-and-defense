#!/usr/bin/env python

def memfrob(string):
    ret = ''
    for c in string:
        ret += chr(ord(c)^42)
    return ret

def add_space(string):
    ret = ''
    for c in string:
        ret += chr((ord(c)+0x20)&0xff)
    return ret

def sub_space(string):
    ret = ''
    for c in string:
        ret += chr((ord(c)-0x20 + 0x100)&0xff)
    return ret


def rev_main():
    string = raw_input()
    r3 = int(string, 16)
    print r3
    i1 = str(r3)
    print i1
    r2 = sub_space(i1)
    print r2
    r1 = memfrob(r2)
    print r1

def main():
    string = raw_input()

    r1 = memfrob(string)
    print r1
    r2 = add_space(r1)
    print r2

    i1 = int(r2)
    print i1
    r3 = "%x" % i1
    print r3


if __name__ == '__main__':
    rev_main()
    main()
