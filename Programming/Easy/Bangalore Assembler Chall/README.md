# Bangalore Assembler Chall

Reading through `Bangalore.asm`, the program follows a basic structure, starting with `_start`, calling `_printString`, then looping through `_flagLoop`. Within `_flagLoop`, the function calls `_Step1`, `_Step2`, `_Step3`, and `_Step4`, each of which we need to edit, before incrementing `rcx`, which serves as an index, letting the program count out 30 loops.

Looking at each of the `_Step`'s, we can see an issue. In each function, `rax`, which includes `return` values, is `mov`ed into `rcx`, overwriting the increment value and breaking the counting of the loop. We can see the result when we try to run the program:

```
$ ./clnasm.sh
+ rm Bangalore
+ rm Bangalore.o
+ rm Data.o
+ nasm -f elf64 -F dwarf -o Bangalore.o Bangalore.asm
+ nasm -f elf64 -F dwarf -o Data.o Data.asm
+ ld Bangalore.o Data.o -o Bangalore
+ set +x
Hello CTFlearn Bangalore Assembler Challenge!
./clnasm.sh: line 17:   184 Segmentation fault      (core dumped) ./Bangalore
139
```

The CTF tells us to only use `push`/`pop` commands. Fortunately, we can save and restore the `rcx` values fairly simply. Reading through the functions tells us that no stack values are overwritten over the course of any of the calls, so we can just add a `push rcx` statement at the start of each `_Step` to save the value at the top of the stack and then add a `pop rcx` statement at the end of each `_Step` before the `ret` to restore the `rcx` value and preserve the increment.

With these modifications (included in the `Bangalore.asm` file), we get:

```
$ ./clnasm.sh
+ rm Bangalore
+ rm Bangalore.o
+ rm Data.o
+ nasm -f elf64 -F dwarf -o Bangalore.o Bangalore.asm
+ nasm -f elf64 -F dwarf -o Data.o Data.asm
+ ld Bangalore.o Data.o -o Bangalore
+ set +x
Hello CTFlearn Bangalore Assembler Challenge!
C
CT
CTF
CTFl
CTFle
CTFlea
CTFlear
CTFlearn
CTFlearn{
CTFlearn{B
CTFlearn{Be
CTFlearn{Ben
CTFlearn{Beng
CTFlearn{Benga
CTFlearn{Bengal
CTFlearn{Bengalu
CTFlearn{Bengalur
CTFlearn{Bengaluru
CTFlearn{Bengaluru_
CTFlearn{Bengaluru__
CTFlearn{Bengaluru__K
CTFlearn{Bengaluru__Ka
CTFlearn{Bengaluru__Kar
CTFlearn{Bengaluru__Karn
CTFlearn{Bengaluru__Karna
CTFlearn{Bengaluru__Karnat
CTFlearn{Bengaluru__Karnata
CTFlearn{Bengaluru__Karnatak
CTFlearn{Bengaluru__Karnataka
CTFlearn{Bengaluru__Karnataka}
0
```

Our flag is `CTFlearn{Bengaluru__Karnataka}`.
