pickles2 = "9d ac 92 eb b3 bf ed e9 e4 97 b9 94 e8 e1 b3 b9 94 bf e3 e1 b7 bf ff fa"
pickles2 = [int(m, 16) for m in pickles2.split(" ")]

output = []
lVar5 = 0
while lVar5 != 0x18:
    l1 = ((pickles2[lVar5] ^ 0xcb) - 0x13) ^ 0xde
    l2 = ((pickles2[lVar5] ^ 0xcb) - 0x72) ^ 0xde
    l3 = ((pickles2[lVar5] ^ 0xcb) - 0xb4) ^ 0xde
    l4 = ((pickles2[lVar5] ^ 0xcb) - 0x13)
    l5 = ((pickles2[lVar5] ^ 0xcb) - 0x72)
    l6 = ((pickles2[lVar5] ^ 0xcb) - 0xb4)
    output.append(
        [
            l1, l2, l3, l4, l5, l6,
            l1 & 0xff,
            l2 & 0xff,
            l3 & 0xff,
            l4 & 0xff,
            l5 & 0xff,
            l6 & 0xff,
        ]
    )
    lVar5 = lVar5 + 1

for i in range(len(output[0])):
    print(f"{i}:", [t[i] for t in output])

print(70 in range(0x20, 0x7f))

for i in range(len(output[0])):
    print(f"{i:<5}" + "".join([chr(o) for o in [t[i] if t[i] in range(0x20, 0x7f) else 0x20 for t in output]]))