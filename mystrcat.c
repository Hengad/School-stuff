#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mystrcat.h"

char *mystrcat(char *dest, const char *src)
{
	int size = 1;
	const char *counter = dest;
	while (*counter++)
		size++;
	counter = src;
	while (*counter++)
		size++;

	char* buffer = malloc(strlen(dest) + 1);
	strcpy(buffer, dest);

	char *newDest = realloc(dest, size * sizeof(char));
	dest = newDest;
	
	for (int i = 0; i < (int)strlen(buffer); i++)
		*newDest++ = buffer[i];
	while (*src)
		*newDest++ = *src++;

	*newDest = 0;
	free(buffer);

	return dest;
}


/*  EXAMPLE USAGE

	char *str = malloc(7);
	strcpy(str, "Aatami");
	str = mystrcat(str, "Beetami");
*/
