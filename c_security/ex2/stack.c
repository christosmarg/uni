#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
bof(char *str)
{
	char buf[24];

	printf("addr: %p\n", buf);
	strcpy(buf, str);
	return (1);
}

int
main(int argc, char *argv[])
{
	FILE *badfp;
	char str[517];

	if ((badfp = fopen("bad", "r")) == NULL)
		err(1, "fopen(bad)");
	fread(str, sizeof(char), 517, badfp);
	fclose(badfp);
	bof(str);
	printf("returned\n");

	return (0);
}
