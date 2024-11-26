//
// Created by umbra on 10/9/24.
//
#include "../includes/libft.h"
#include "../includes/parsing_error.h"
#include "minishell.h"

void	print_parsing_error(t_erreur err)
{
	if (err.error_code == -1)
		return ;
	if (err.error_code == STX_ALLOC)
	{
		ft_putendl_fd("Allocation failed", 2);
		return ;
	}
	ft_putstr_fd("bash: syntax error near unexpected token `", ERROR_FD);
	if (err.error_code == STX_NL)
		ft_putstr_fd("newline", ERROR_FD);
	else if (err.error_code == SYNTAX)
		ft_putchar_fd(err.c, ERROR_FD);
	else if (err.error_code == D_SYNTAX)
	{
		ft_putchar_fd(err.c, ERROR_FD);
		ft_putchar_fd(err.c, ERROR_FD);
	}
	ft_putstr_fd("'\n", ERROR_FD);
}

void error(int i, char *str)
{
    if (i == 1)
    {
        write(2, "Wrong arguments\n", 17);
    }
    else if (i == 2)
    {
        write(2, "Command not found : ", 21);
        if (str)
        {
            write(2, str, strlen(str));
        }
        write(2, "\n", 1);
    }
    else if (i == 3)
    {
        write(2, "no such file or directory : ", 29);
        if (str)
        {
            write(2, str, strlen(str));
        }
        write(2, "\n", 1);
    }
    exit(EXIT_FAILURE);
}

void    free_command(char **cmd)
{
    int i;

    i = 0;
    if (!cmd)
        return;
    while (cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}