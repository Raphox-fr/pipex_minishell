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

void display_error(char *cmd, char *mess, int errno_code, char **args)
{
	int x;
	x = 0;

	char *return_sterror;

	if (errno_code == ENOENT) // no such file or directory
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (args != NULL)
		{
			display_args(args);
			write(2, ": ", 2);
		}
		return_sterror = strerror(errno_code);
		write(2, return_sterror, ft_strlen(return_sterror));
		write(2, "\n", 1);
	}

	else if (errno_code == ENOTDIR) // no such file or directory
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (args != NULL)
		{
			display_args(args);
			write(2, ": ", 2);
		}
		return_sterror = strerror(errno_code);
		write(2, return_sterror, ft_strlen(return_sterror));
		write(2, "\n", 1);
	}
	else if (errno_code == EACCES) // no such file or directory
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (args != NULL)
		{
			display_args(args);
			write(2, ": ", 2);
		}
		return_sterror = strerror(errno_code);
		write(2, return_sterror, ft_strlen(return_sterror));
		write(2, "\n", 1);
	}
	else if (errno_code == ELOOP) // no such file or directory
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (args != NULL)
		{
			display_args(args);
			write(2, ": ", 2);
		}
		return_sterror = strerror(errno_code);
		write(2, return_sterror, ft_strlen(return_sterror));
		write(2, "\n", 1);
	}
	else if (errno_code == ENAMETOOLONG) // no such file or directory
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (args != NULL)
		{
			display_args(args);
			write(2, ": ", 2);
		}
		return_sterror = strerror(errno_code);
		write(2, return_sterror, ft_strlen(return_sterror));
		write(2, "\n", 1);
	}



	return ;
	

	// else if (ft_strncmp(error, "cmd not found", ft_strlen(cmd)) == 0)
	// {	write(2, cmd, ft_strlen(cmd));
	// 	write(2, ":", 1);
	// 	write(2, " command not found\n", 19);
	// }
}

void display_args(char **args)
{
	int fd[2];
	pipe(fd);

	char buffer[10000];
	size_t	bytes_read;
	
	int i;
	i = 0;
	if (args == NULL)
	{
		return ;
	}
	
	while (args[i] != NULL)
	{
		write(fd[1], args[i], ft_strlen(args[i]));
		i++;
	}
	bytes_read = read(fd[0], buffer, sizeof(buffer));
	write(2, buffer, bytes_read);
	close(fd[0]);
	close(fd[1]);
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