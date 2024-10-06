pickles1 = "9e ad 93 b5 bc b8 ee ea e5 90 ba b8 eb ba ed e3 e8 bc ee ba ed eb b8 ee ec fb"
pickles1 = [int(m, 16) for m in pickles1.split(" ")]

output = []
lVar5 = 0
while lVar5 != 0x1a:
    l1 = ((pickles1[lVar5] ^ 0xcb) - 0x12) ^ 0xde
    l2 = ((pickles1[lVar5] ^ 0xcb) - 0x71) ^ 0xde
    l3 = ((pickles1[lVar5] ^ 0xcb) - 0xb3) ^ 0xde
    l4 = ((pickles1[lVar5] ^ 0xcb) - 0x12)
    l5 = ((pickles1[lVar5] ^ 0xcb) - 0x71)
    l6 = ((pickles1[lVar5] ^ 0xcb) - 0xb3)
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
    print(f"{i + 1}:", [t[i] for t in output])

print(70 in range(0x20, 0x7f))

for i in range(len(output[0])):
    print(
        f"{i:<5}" + "".join(
            [chr(o) for o in [t[i] if t[i] in range(0x20, 0x7f) else 0x20 for t in output]]
        )
    )