#include"shell.h"
/**
 * printEnvironment - prints the environment of the user
 * Return: Nothing
*/
void printEnvironment(void)
{
    int i = 0;
    int j = 0;
    while (environ[i] != NULL)
    {
        j = 0;
        while(environ[i][j] != '\0')
        {
            _putchar(environ[i][j]);
            j++;
        }
        _putchar('\n');            
        i++;       
    }
}