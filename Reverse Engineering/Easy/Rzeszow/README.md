# Rzeszow

A quick test of the executable shows us:

```
Welcome to the CTFlearn Rzeszow Reversing Challenge! v2
Error: The flag must begin with CTFlearn{
```

We won't be getting further trying random inputs, so we open the executable in Ghidra to disassemble the code. (The raw disassembled main function is included in `main.c`.)

First, we see on line 66:

```
if (__s[sVar6 - 1] == 0x7d)
```

and on line 67:

```
if (sVar6 == 0x14)
```

This tells us that the total paylaod string is 20 characters long, and discounting the 9 characters of `CTFlearn{` and the 1 character of `}`, this gives us a 10-character kernel. If we try to enter `CTFlearn{aaaaaaaaaa}`, we get:

```
Welcome to the CTFlearn Rzeszow Reversing Challenge! v2
Flag kernel is: aaaaaaaaaa
Sorry, bad flag dude!
```

So, we're on the right track.

Looking further, lines 75 through 101 cover a possible helper passage that can be triggered by add the `-v` flag at the end of the executable command, which gives us some insight into the encoding process of the kernel. In particular, it gives us a string that serves as a reference table (you can verify this with some experimention of the kernel inputs):

```
The flag is hidden in here somewhere:
W8Hj?1VESL^g4xwcvtW%humtEosd$Fq^dXPvi$#sSEe@o618Zl9.5PFrvC%O_E*LB%Igl8qur9SuLAp4MkK#pRzwJHI*Fn9mUs%mGK^RQKO.G*JFJvV%?VJpCpVF9eJuz5&kB!&_VF5DrF?U?jfm&x^9aC7X2(&cGGzbLbOsSOuBeq*ZT%fpc&9riTDO5X%RuTKI@vCqu#CsTAp$Q9WoXJv96.ySdB2EfMK*$NX?.U*aDrfPQQPhFB9cC6y0hMGvbgjBogSux65gTL#Cm9TQt7nTayu9Vr%thh2GnnikE8JnIwlHfreZep^sZ6IrnXT#qu50Lv.Rd_XPDfgwzWcJ3ISjKM!ftRllVyF$?RE_dcJT5&uKZJ!WsqR853uLzcs!8&VyRuTDsiq#6PdmBNlPI$tPi?wZ5$ACCf9yda!OkP.Dc73Nx.Nt1Rj0O.?P!sZDB^d0LN1qXR31!t?OZ#mm7SfZHPO*4gx1J0nyC^d2EKeq^f4h7mSqaIcMv0ZT@G0M
```

The string encoding is reference as `kernelenc`.

Reversing the code in lines 75 through 101, we see that we convert a given character `c = kernelenc[0xbaadf00d % uVar9 & 0x1ff]`. `uVar9`, in turn, is composed of the ASCII value of the current char (`iVar15`) to the power of 3 plus the ASCII value of the current char (`iVar15`) to the power of 2 plus the current index of the char in the input kernel times 3; this is from line 85:

```
uVar9 = iVar15 * iVar15 * iVar15 + iVar15 * iVar15 + iVar5;
```

We can use Python to brute-force the possible input values the encoding schema, as shown in `reverse.py` in this repo. This gives us the kernel: `K0nstancja`. It's not entirely clear off the bat if this is the solution, but running the kernel shows:

```
$ ./Rzeszow CTFlearn{K0nstancja}
Welcome to the CTFlearn Rzeszow Reversing Challenge! v2
Flag kernel is: K0nstancja
Woot Woot, you found the flag: CTFlearn{K0nstancja}
```

So, our flag is `CTFlearn{K0nstancja}`.