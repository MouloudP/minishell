#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char **cmd_in_arg;
    int i = 0;

    cmd_in_arg = malloc(sizeof(char *) * 3);
	cmd_in_arg[0] = "12121";
    cmd_in_arg[1] = "dawdwadw";
    cmd_in_arg[2] = NULL;
    while (cmd_in_arg[i])
    {
	    printf("%s\n", cmd_in_arg[i]);
        i++;
    }
    printf("%s\n", cmd_in_arg[i]);
}