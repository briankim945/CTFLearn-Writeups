# Impossible equation

Looking at the C code tells us that we need to solve for `X` where `X * 212103456793011 = 183057226632645` where all the numbers involved are unsigned longs. 183057226632645 is less than 212103456793011, so we will need to loop around. Now, we could write a loop in C to test possible value of `X`, but that would take too long. A quick search tells us that an unsigned long ranges from 0 to 18446744073709551615. That means we need to solve for two numbers, `X` and `Y`, both of which are positive integers, such that $X * 212103456793011 = Y * 2^{64}+ 183057226632645$.
At this point, we can treat this as more of a modulo math problem than a coding problem. Assume that all equations below are in module $2^{64}$.

$$
X = \frac{Y * 2^{64}+ 183057226632645}{212103456793011}

$$

Carrying out divison in modulo means finding the modular multiplicative inverse, so we write a quick script to use the extended Euclidean algorithms to find the inverse. The script (`inverse.py` in the same folder) gives us $6234943569730532731$.

Now, we can calculate:

$$
X mod 2^{64} = \frac{Y * 2^{64}+ 183057226632645}{212103456793011}

$$

$$
X = (Y * 2^{64}+ 183057226632645) * 6234943569730532731

$$

$$
X = 9585860797856392871

$$

If we run `nc rivit.dev 10011` and enter out $X$ value, we get:

```
~$ nc rivit.dev 10011
X * 212103456793011 = 183057226632645
X = ? 9585860797856392871
result: 183057226632645
CTFlearn{ju5t_4_m0dul0_3qu4t10n}

```

## References

[https://www.extendedeuclideanalgorithm.com/xea.php](https://www.extendedeuclideanalgorithm.com/xea.php)
