/* myecho.c */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("[SON]: in son \n");
	int j;
	for (j = 0; j < argc; j++)
		printf("[SON]: argv[%d]: %s\n", j, argv[j]);

	exit(EXIT_SUCCESS);
}