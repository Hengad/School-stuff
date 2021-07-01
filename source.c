#include "source.h"
#include <ctype.h>
#include <string.h>

char *my_toupper1(char *dest, const char *src)
{
	strcpy(dest, "\0");
	const char *next = src;

	while (*next)
	{
		char tmp[4] = { 0 };
		if (*next == '?')
			tmp[0] = '!';
		else if (*next == '.')
			for (int i = 0; i < 3; i++)
				tmp[i] = '!';
		else if (*next == '�')
			tmp[0] = 142;
		else if (*next == '�')
			tmp[0] = 143;
		else if (*next == '�')
			tmp[0] = 153;
		// LIS�SIN HUVIKSENI VIEL� TUEN POHJOISMAISILLE KIRJAIMILLE.
		else
			tmp[0] = toupper((unsigned char)*next);
		strcat(dest, tmp);
		next++;
	}
	return dest;
}

char *my_toupper2(char *dest, const char *src)
{
	int r = 0;
	int w = 0;
	while (src[r] != '\0')
	{
		if (src[r] == '?')
			dest[w] = '!';
		else if (src[r] == '.')
		{
			for (int i = w; i < w+3; i++)
				dest[i] = '!';
			w += 2;
		}
		else
			dest[w] = toupper(src[r]);
		w++;
		r++;
	}
	dest[w] = '\0';
	return dest;
}