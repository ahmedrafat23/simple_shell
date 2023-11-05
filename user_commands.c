#include "shell.h"

/**
 * exitShell - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if data.argv[0] != "exit"
 */
int exitShell(info_t *data)
{
	int exitCheck;

	if (data->arguments[1]) /* If there is an exit argument */
	{
		exitCheck = stringToInteger(data->arguments[1]);
		if (exitCheck == -1)
		{
			data->status = 2;
			printError(data, "Illegal number: ");
			printString(data->arguments[1]);
			printCharacter('\n');
			return (1);
		}
		data->errorNumber = stringToInteger(data->arguments[1]);
		return (-2);
	}
	data->errorNumber = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int changeDirectory(info_t *data)
{
	char *s, *dir, buffer[1024];
	int chdirReturn;

	s = getCurrentWorkingDirectory(buffer, 1024);
	if (!s)
		printString("TODO: >>getcwd failure emsg here<<\n");
	if (!data->arguments[1])
	{
		dir = getEnvironmentVariable(data, "HOME=");
		if (!dir)
			chdirReturn = /* TODO: what should this be? */
				changeCurrentDirectory((dir = getEnvironmentVariable(data, "PWD=")) ? dir : "/");
		else
			chdirReturn = changeCurrentDirectory(dir);
	}
	else if (compareStrings(data->arguments[1], "-") == 0)
	{
		if (!getEnvironmentVariable(data, "OLDPWD="))
		{
			printString(s);
			printCharacter('\n');
			return (1);
		}
		printString(getEnvironmentVariable(data, "OLDPWD="));
		printCharacter('\n');
		chdirReturn = /* TODO: what should this be? */
			changeCurrentDirectory((dir = getEnvironmentVariable(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirReturn = changeCurrentDirectory(data->arguments[1]);
	if (chdirReturn == -1)
	{
		printError(data, "can't cd to ");
		printString(data->arguments[1]);
		printCharacter('\n');
	}
	else
	{
		setEnvironmentVariable(data, "OLDPWD", getEnvironmentVariable(data, "PWD="));
		setEnvironmentVariable(data, "PWD", getCurrentWorkingDirectory(buffer, 1024));
	}
	return (0);
}

/**
 * helpCommand - displays help message
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int helpCommand(info_t *data)
{
	char **argumentsArray;

	argumentsArray = data->arguments;
	printString("help call works. Function not yet implemented \n");
	if (0)
		printString(*argumentsArray); /* temp att_unused workaround */
	return (0);

