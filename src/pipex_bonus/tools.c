/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:38:34 by rafaria           #+#    #+#             */
/*   Updated: 2024/12/11 18:50:54 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


	// if (arguments != NULL)
	// {
	// 	dir = opendir(arguments[0]);
	// 	if (dir == NULL)
	// 	{
	// 		display_error("cd", NULL, errno, arguments);
	// 		closedir(dir);
	// 		return(envp);
	// 	}
	// }

int handle_redirection(t_data_rule data)
{
	int i;

	i = 0;
	
	if (data.oper[i] != 0)
		i = 0;
	else
		return (0);

	while (data.out[i] != NULL)
	{
		if (data.oper[i] == '<' && handle_entry_redirections(data, data.oper[i], data.input) == -1)
		{
			return (-1);
		}
    	else if (data.oper[i] == 'h' && handle_heredoc(data.input) == -1)
    	{
			return (-1);
    	}
		else if ((data.oper[i] ==  '>' || data.oper[i] ==  'r') &&  handle_exit_redirections(data, data.oper[i], data.out[i]) == -1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
	
int handle_exit_redirections(t_data_rule data, char oper, char *output)
{
    int fd;
	
	
    if (oper ==  '>')
    {
        fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			display_error(data.command, output, errno, data.arguments);
			close(fd);
			return (-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
		return(0);
    }
    else if (oper ==  'r')
    {
		write(2, "coucou", 6);
        fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd == -1)
        {
			display_error(data.command, NULL, errno, data.arguments);
			return (-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
		return (0);

    }
	return (0);
	
}

int		handle_entry_redirections(t_data_rule data, char oper, char *input)
{
	int fd;
	
	if (oper ==  '<')
    	{
        	fd = open(input, O_RDONLY);
        	if (fd == -1)
        	{
				display_error(data.command, NULL, errno, data.arguments);
				return (-1);
        	}
        	dup2(fd, STDIN_FILENO);
        	close(fd);
    	}
		return (0);
}

int handle_heredoc(char *delimiter)
{
    char *line;
    int   pipe_fds[2];

    if (pipe(pipe_fds) == -1)
    {
        perror("Erreur lors de la création du pipe");
    }
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            printf("CTRL D PRESSED \n");
			close(pipe_fds[1]);
			close(pipe_fds[0]);
			return (-1);
        }
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fds[1], line, ft_strlen(line));
        write(pipe_fds[1], "\n", 1);
        free(line);
    }
    close(pipe_fds[1]);
    dup2(pipe_fds[0], STDIN_FILENO);
    close(pipe_fds[0]);
	return (0);
}

	



void wait_for_children(void)
{
    int status;

    while (wait(&status) > 0)
    {
        // attends
    }
}
void free_split(char **strs)
{
    int i = 0;

    while (strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}

char *find_path_in_paths(char **paths, char *cmd)
{
    int i;
    char *path;
    char *part_path;

    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/", 0);
        if (!part_path)
            return (NULL);
        path = ft_strjoin(part_path, cmd, 0);
        free(part_path);
        if (!path)
            return (NULL);
        if (access(path, F_OK | X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    return (NULL);
}

char *find_path(char *cmd, char **envv)
{
    int i;
    char **paths;
    char *path;

    i = 0;
    while (envv[i] && ft_strnstr(envv[i], "PATH", 4) == 0)
        i++;
    if (!envv[i])
        return (NULL);
    paths = ft_split(envv[i] + 5, ':');
    if (!paths)
        return (NULL);
    path = find_path_in_paths(paths, cmd);
    free_split(paths);
    return (path);
}




