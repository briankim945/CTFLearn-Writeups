# Positive challenge

Running the command ``nc rivit.dev 10010`` seems to give us a loop where we enter numbers to a variable `a`. Adding too large numbers seems to cause some looping.

Opening the given `task.c` file gives us a better sense of what's happening behind the scenes:

```
#include <stdlib.h>
#include <stdio.h>

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

	short acc = 0;
	short n;
	while(acc >= 0){
		printf("acc = %d\n", acc);
		printf("Enter a number to add: ");
		if(scanf("%hd", &n) != 1){
			while(getchar() != '\n');
			puts("Invalid value");
			continue;
		}

		if(n < 0){
			n = abs(n);
		}

		n %= 100;
		acc += n;
		acc %= 100;
	}

	system("cat ./flag.txt");
}

```

So, we need to find a way to get `acc`'s value under 0 to get the contents of `flag.txt`. Notably, we can't add negative numbers, as the program manually sets negative values of `n` to their absolute value. `n` and `acc` are also calculated with by `mod 100` to prevent values from running too high. However, if we can get `acc` to a negative value, then that won't matter.

A quick Google search tells us that the limits of a `short` in C are -32767 to +32767. If we try to go one over to 32768, then C should interpret that as less than 0, keeping the value of `n` as 32768. C will interpret this as a negative `short`, meaning that `n` will be a negative modulo and `acc` will be negative.

Our results from running:

```
$ nc rivit.dev 10010
acc = 0
Enter a number to add: 32768
CTFlearn{n0t_s0_p0s1t1v3_4t_4ll}
```
