#include <stdio.h>

int main() {
		
	char str[100];
	printf("enter anything: ");
	fgets(str, 100, stdin);
	printf("you entered: %s\n", str );
	return 0;
}
