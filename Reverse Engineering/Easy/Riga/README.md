# Riga

Running the given exectuable tells us that we need to input the flag as an argument. Opening the code in GDB looks unpromising, so for this challenge, we start by disassembling the given executable via Ghidra. The main function looks like this:

```
undefined8 main(int param_1,long param_2)

{
  char *__src;
  char cVar1;
  byte *pbVar2;
  undefined8 uVar3;
  long lVar4;
  byte *pbVar5;
  undefined8 *puVar6;
  
  puVar6 = (undefined8 *)&buffer;
  for (lVar4 = 0x20; lVar4 != 0; lVar4 = lVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  StewedSaurkraut0();
  if (param_1 == 1) {
    StewedSaurkraut1();
    uVar3 = 1;
  }
  else {
    __src = *(char **)(param_2 + 8);
    pbVar5 = &buffer;
    strncpy(&buffer,__src,0x100);
    while( true ) {
      pbVar2 = (byte *)strlen(__src);
      if (pbVar2 <= pbVar5 + -0x104100) break;
      *pbVar5 = *pbVar5 ^ 0xde;
      pbVar5 = pbVar5 + 1;
    }
    BlackRyeBread();
    if (beerEmbassy == 0) {
      cVar1 = HerbalTea1(&buffer);
    }
    else if (beerEmbassy == 1) {
      cVar1 = HerbalTea0(&buffer);
    }
    else {
      cVar1 = HerbalTea2(&buffer);
    }
    if (cVar1 == '\0') {
      __printf_chk(1,"Sorry, you did not find the flag %s\n",__src);
      uVar3 = 2;
    }
    else {
      __printf_chk(1,"Congratulations!! You found the flag %s\n",__src);
      uVar3 = 0;
    }
  }
  return uVar3;
}
```

While the code looks pretty confusing, skipping towards the end, we see that the key variable is `cVar1`, which is returned by one of the `HerbalTea` functions. Opening `HerbalTea0` looks like:

```
undefined8 HerbalTea0(char *param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  size_t sVar4;
  long lVar5;
  timeval local_18;
  
  iVar3 = gettimeofday(&local_18,(__timezone_ptr_t)0x0);
  lVar5 = 0;
  if (iVar3 == 0) {
    lVar5 = local_18.tv_sec;
  }
  if ((2 < lVar5 - potato0) || (sVar4 = strlen(param_1), sVar4 != 0x1e)) {
    return 0;
  }
  *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) ^ 0xdededede;
  lVar5 = 0;
  *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) ^ 0xdede;
  *(ulong *)param_1 = *(ulong *)param_1 ^ 0xdededededededede;
  *(ulong *)(param_1 + 8) = *(ulong *)(param_1 + 8) ^ 0xdededededededede;
  *(ulong *)(param_1 + 0x10) = *(ulong *)(param_1 + 0x10) ^ 0xdededededededede;
  do {
    cVar1 = param_1[lVar5];
    bVar2 = cVar1 + 0x11;
    if (bVar2 < 0x7f) {
      if (bVar2 < 0x20) {
        bVar2 = cVar1 + 0x70;
      }
      if ((bVar2 ^ 0xcb) != pickles0[lVar5]) {
        return 0;
      }
    }
    else if ((byte)(cVar1 + 0xb2U ^ 0xcb) != pickles0[lVar5]) {
      return 0;
    }
    lVar5 = lVar5 + 1;
    if (lVar5 == 0x1e) {
      return 1;
    }
  } while( true );
}
```

The basic structure of the function seems clear: a series of XOR and addition functions are carried out over each character in `param_1`, which seems to be our input. The result is compared against `pickles0`, which we can extract from the data using Ghidra.

Looking at `HerbalTea1` and `HerbalTea2`, we see essentially the same layout, with a few variations in the constant values that `param_1`'s chars are summed with and XORed against.

We can extract each `pickle` value and write a Python script that reverses the XOR and addition operations for each `HerbalTea`. Notably, there are a few branching `if` statements based on the input `char` value and varying stretche of the input `param_1` that are XORed againt `0xde`, so we will need try to execute all possible variations and compare for the sensible solution.

For code comparisons, my Python scripts are in this folder under `HerbalTea0.py`, `HerbalTea1.py`, and `HerbalTea2.py`. Printing out possible `param_1`s gives us `CTFlearn{Daugava_R1ver_Latv1a}`, `CTFlearn{I_am_super_smart}`, and `CTFlearn{I_Love_Latvia!}`. The disassembled code tells us that the correct solution is based on time inputs, but if we just try each of them, we find that:

```
./Riga CTFlearn{Daugava_R1ver_Latv1a}
Welcome to the CTFLearn.com Riga Reversing Challenge!
Congratulations!! You found the flag CTFlearn{Daugava_R1ver_Latv1a}
```

Entering this into CTFLearn gives us our confirmation.
