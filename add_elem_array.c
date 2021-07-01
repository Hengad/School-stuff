#include "add_elem_array.h"
#include <stdlib.h>
#include <stdio.h>

int *add_elem_array(int *arr, unsigned int num, int newval)
{
	int *newArr = malloc(num * sizeof(int));
	for (unsigned int i = 0; i < num; i++)
		newArr[i] = arr[i];
	arr = (int*)realloc(arr, (num + 1) * sizeof(int));
	for (unsigned int i = 0; i < num; i++)
		arr[i] = newArr[i];
	arr[num] = newval;
	free(newArr);
	return arr;
}

// EXAMPLE USAGE: array = add_elem_array(array, 5, 10);
// TO PUSH BACK VALUE 10 TO ARRAY OF SIZE 5
