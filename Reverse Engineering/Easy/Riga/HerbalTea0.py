pickles0 = "9f ae 9c b6 bd b9 ef eb e6 9e b9 ec b3 b9 e3 b9 bb a8 89 e3 bd ef bb 96 b9 ed e3 89 b9 e4"
pickles0 = [int(m, 16) for m in pickles0.split(" ")]

output = []
lVar5 = 0
while lVar5 != 0x1e:
    l1 = ((pickles0[lVar5] ^ 0xcb) - 0x11) ^ 0xde
    l2 = ((pickles0[lVar5] ^ 0xcb) - 0x70) ^ 0xde
    l3 = ((pickles0[lVar5] ^ 0xcb) - 0xb2) ^ 0xde
    l4 = ((pickles0[lVar5] ^ 0xcb) - 0x11)
    l5 = ((pickles0[lVar5] ^ 0xcb) - 0x70)
    l6 = ((pickles0[lVar5] ^ 0xcb) - 0xb2)
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