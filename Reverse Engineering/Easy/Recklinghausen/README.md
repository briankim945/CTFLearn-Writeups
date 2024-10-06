# Recklinghausen

Trying to run the executable, we find that we need to run the executable with the correct flag as an argument.

Opening the executable with `gdb` and running `disas main` reveals an interesting function calle `_Z13get_wall_timev`. The seeming use of the function becomes apparent when we try to add breakpoints in the executable. It seems that there is an internal timer to prevent us from spending too long in a debugger.

Instead, we try to decompile the executable using Ghidra. Opening the `main` function in Ghidra, we see a function called `checkMsg`. Based on the decompile, and after experimenting with some data types, it seems to be operating on the input with a variable called `msg5`:

```
/* CheckMsg(char const*) */

undefined8 CheckMsg(char *param_1)

{
  size_t sVar1;
  long lVar2;
  uint uVar3;
  
  sVar1 = strlen(param_1);
  uVar3 = (uint)(byte)msg5[0];
  if (uVar3 != sVar1) {
    return 0;
  }
  if (uVar3 != 0) {
    lVar2 = 0;
    do {
      if (msg5[lVar2 + 2] != (char)(param_1[lVar2] ^ msg5[1])) {
        return 0;
      }
      lVar2 = lVar2 + 1;
    } while ((int)lVar2 < (int)uVar3);
  }
  return 1;
}
```

If we follow `msg5` into the data, we can extract the following list of hex values:

`21 7e 3d 2a 38 12 1b 1f 0c 10 05 2c 0b 16 0c 18 1b 0d 0a 0d 0e 17 1b 12 1b 21 38 1b 0d 0a 17 08 1f 12 03 00`

Next, we can try to reconstruct the input string by reversing the XOR:

```
msg5 = "21 7e 3d 2a 38 12 1b 1f 0c 10 05 2c 0b 16 0c 18 1b 0d 0a 0d 0e 17 1b 12 1b 21 38 1b 0d 0a 17 08 1f 12 03 00"
msg5 = [int(m, 16) for m in msg5.split(" ")]

output = [0] * len(msg5)

for i in range(msg5[0]):
    output[i] = msg5[1] ^ msg5[i + 2]

print("".join([chr(o) for o in output]))
```

Code included in `string_construct.py`.

Running the code gives us `CTFlearn{Ruhrfestspiele_Festival}`, and if we enter this in the executable, we get:

```
./Recklinghausen CTFlearn{Ruhrfestspiele_Festival}
Welcome to the Recklinghausen Reversing Challenge!
Compile Options: ${CMAKE_CXX_FLAGS} -O0 -fno-stack-protector -mno-sse
CONGRATULATIONS!! You found the flag!! : CTFlearn{Ruhrfestspiele_Festival}
All Done!
```
