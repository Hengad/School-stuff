char *delete_comments(char *input)
{
	char *readyString = NULL;
	char* inputBlockStartPtr = input;
	char* origInput = input;

	int stringSize = 0;
	int blockSize = 0;

	int oneLiner = 0;

	while (*input)
	{
		if (!memcmp(input, "//", 2) || !memcmp(input, "/*", 2))
		{
			if (!memcmp(input, "//", 2))
				oneLiner = 1;
			else
				oneLiner = 0;
			if (blockSize)
			{
				// kopioidaan readyString uuteen lokaatioon jonka kokoa on kasvatettu tulevan blokin verran
				stringSize += blockSize;
				char* deepCopy = malloc(stringSize);
				memcpy(deepCopy, readyString, stringSize - blockSize);
				readyString = realloc(readyString, stringSize);
				memcpy(readyString, deepCopy, stringSize - blockSize);
				free(deepCopy);

				// kopioidaan blokki readyStringin perään
				memcpy(readyString + (stringSize - blockSize), inputBlockStartPtr, blockSize);
				blockSize = 0;
			}
			while (*input)
			{
				input++;
				if (oneLiner)
				{
					if (!memcmp(input, "\n", 1))
					{
						input++;
						inputBlockStartPtr = input;
						break;
					}
				}
				else
				{
					if (!memcmp(input, "*/", 2))
					{
						input += 2;
						inputBlockStartPtr = input;
						break;
					}
				}
			}
		}
		blockSize++;
		input++;
	}

	stringSize += blockSize;
	char* deepCopy = malloc(stringSize);
	memcpy(deepCopy, readyString, stringSize - blockSize);
	readyString = realloc(readyString, stringSize + 1);
	memcpy(readyString, deepCopy, stringSize - blockSize);
	free(deepCopy);

	memcpy(readyString + (stringSize - blockSize), inputBlockStartPtr, blockSize);
	memset(readyString + stringSize, 0, 1);

	memcpy(origInput, readyString, stringSize + 1);
	free(readyString);

	return origInput;
}
