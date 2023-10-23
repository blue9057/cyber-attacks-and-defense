# Running challenges

All the binaries require shellcode.bin to read the shellcode in a binary format.
Please use the shellcode-template to write the shellcode, and run either
`make 32` for 32 bit or `make 64` for 64 bit shellcode. The command will
generate shellcode.bin file.

You can also use `make print` to print out your shellcode directly
on the console, or you can run `make objdump` to check both opcode
and the assembly of the shellcode that you wrote in the shellcode.S file.
