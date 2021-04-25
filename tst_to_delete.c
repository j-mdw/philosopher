#include <stdio.h>


void
	print(char *s)
{
	printf("%s\n", s);
}

main()
{
	char *a = "Hello";

	print(a + "=bonjour");
}
