#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "filestats.h"

int line_count(const char *filename)
{
    FILE* file = NULL;
    file = fopen(filename, "r");
    if(file == NULL)
        return -1;
    // this waste of space needs to be fixed
    char s[33000] = "";
    int n = 0;

    while(fgets(s, 33000, file))
        n++;

    if(strlen(s) == 1)
        n--;

    fclose(file);
    return n;
}

int word_count(const char *filename)
{
    int wasSpace = 1;
    FILE* file = NULL;
    file = fopen(filename, "r");
    if(file == NULL)
        return -1;
    char c = 0;
    int n = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if(isalpha(c) && wasSpace)
        {
            wasSpace = 0;
            n++;
        }
        else if(isspace(c))
            wasSpace = 1;
    }
    fclose(file);
    return n;
}
