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
	    printf("%d\n", n);
	    printf("%hd\n", n);
	    printf("%hd\n", n < 0);
	    printf("%d\n", abs(n));
	    printf("%hd\n", abs(n));
	    printf("%hd\n", n % 100);

		if(n < 0){
			n = abs(n);
		}

		n %= 100;
		acc += n;
		acc %= 100;
	}

	system("cat ./flag.txt");
}
