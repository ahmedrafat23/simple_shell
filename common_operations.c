#include "shell.h"

/**
 * determineInteractiveMode - returns true if the shell is in interactive mode
 * @information: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int determineInteractiveMode(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readFileDesc <= 2);
}

/**
 * isCharacterDelimiter - checks if a character is a delimiter
 * @charToCheck: the character to check
 * @delimiterString: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isCharacterDelimiter(char charToCheck, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == charToCheck)
			return (1);
	return (0);
}

/**
 * isAlphabetical - checks for an alphabetic character
 * @charToCheck: The character to check
 * Return: 1 if charToCheck is alphabetic, 0 otherwise
 */
int isAlphabetical(int charToCheck)
{
	if ((charToCheck >= 'a' && charToCheck <= 'z') || (charToCheck >= 'A' && charToCheck <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertStringToInteger - converts a string to an integer
 * @stringToConvert: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convertStringToInteger(char *stringToConvert)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; stringToConvert[index] != '\0' && flag != 2; index++)
	{
		if (stringToConvert[index] == '-')
			sign *= -1;

		if (stringToConvert[index] >= '0' && stringToConvert[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stringToConvert[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

