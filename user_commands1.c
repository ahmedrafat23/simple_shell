#include "shell.h"

/**
 * displayCommandHistory - displays the history list, one command by line,
 *                        preceded with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int displayCommandHistory(info_t *data)
{
    printList(data->commandHistory);
    return 0;
}

/**
 * removeUserAlias - removes user-defined alias
 * @data: parameter struct
 * @aliasString: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int removeUserAlias(info_t *data, char *aliasString)
{
    char *equalsSign, character;
    int result;

    equalsSign = findCharacter(aliasString, '=');
    if (!equalsSign)
        return 1;
    character = *equalsSign;
    *equalsSign = 0;
    result = deleteNodeAtIndex(&(data->userAliases),
        findNodeIndex(data->userAliases, startsWithNode(data->userAliases, aliasString, -1)));
    *equalsSign = character;
    return result;
}

/**
 * setUserAlias - sets user-defined alias
 * @data: parameter struct
 * @aliasString: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int setUserAlias(info_t *data, char *aliasString)
{
    char *equalsSign;

    equalsSign = findCharacter(aliasString, '=');
    if (!equalsSign)
        return 1;
    if (!*++equalsSign)
        return removeUserAlias(data, aliasString);

    removeUserAlias(data, aliasString);
    return (addNodeEnd(&(data->userAliases), aliasString, 0) == NULL);
}

/**
 * printUserAlias - prints a user-defined alias string
 * @aliasNode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printUserAlias(list_t *aliasNode)
{
    char *aliasName = NULL, *aliasValue = NULL;

    if (aliasNode)
    {
        aliasName = findCharacter(aliasNode->str, '=');
        for (aliasValue = aliasNode->str; aliasValue <= aliasName; aliasValue++)
            putcharCharacter(*aliasValue);
        putcharCharacter('\'');
        printString(aliasName + 1);
        printString("'\n");
        return 0;
    }
    return 1;
}

/**
 * manageUserAliases - manages user-defined aliases
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int manageUserAliases(info_t *data)
{
    int i = 0;
    char *aliasChar = NULL;
    list_t *aliasNode = NULL;

    if (data->argumentCount == 1)
    {
        aliasNode = data->userAliases;
        while (aliasNode)
        {
            printUserAlias(aliasNode);
            aliasNode = aliasNode->next;
        }
        return 0;
    }
    for (i = 1; data->arguments[i]; i++)
    {
        aliasChar = findCharacter(data->arguments[i], '=');
        if (aliasChar)
            setUserAlias(data, data->arguments[i]);
        else
            printUserAlias(startsWithNode(data->userAliases, data->arguments[i], '='));
    }

    return 0;

