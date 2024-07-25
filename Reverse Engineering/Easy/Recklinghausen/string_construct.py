msg5 = "21 7e 3d 2a 38 12 1b 1f 0c 10 05 2c 0b 16 0c 18 1b 0d 0a 0d 0e 17 1b 12 1b 21 38 1b 0d 0a 17 08 1f 12 03 00"
msg5 = [int(m, 16) for m in msg5.split(" ")]

output = [0] * len(msg5)

for i in range(msg5[0]):
    output[i] = msg5[1] ^ msg5[i + 2]

print("".join([chr(o) for o in output]))