#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
bof(char *str)
{
	char buf[24];

	strcpy(buf, str);
	return (1);
}

int
main(int argc, char *argv[])
{
	char str[517];
	FILE *badfile;
	
	badfile = fopen("badfile", "r");
	fread(str, sizeof(char), 517, badfile);
	bof(str);
	printf("returned properly\n");

	return (1);
}
