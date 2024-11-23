/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:16 by raphox            #+#    #+#             */
/*   Updated: 2024/11/21 17:40:22 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void display_env(char **envv)
{
	int fd[2];
	pipe(fd);

	char buffer[100000];
	size_t	bytes_read;
	
	int i;
	i = 0;
	
	while (envv[i] != NULL)
	{
		write(fd[1], envv[i], ft_strlen(envv[i]));
		write(fd[1], "\n", 1);
		i++;
	}
	bytes_read = read(fd[0], buffer, sizeof(buffer));
	write(1, buffer, bytes_read);
	close(fd[0]);
	close(fd[1]);
}


// int main(int argc, char **argv, char **envp)
// {
// 	display_env(envp);

// void	execute(char *string, char **envp)
// {
// 	int		i;
// 	char	*chemin;
// 	char	*path;
// 	char	**cmd;

// 	chemin = "/usr/bin/";
	
// 	path = NULL;
	
// 	cmd = ft_split(string, ' ');
// 	if (!cmd || !cmd[0])
// 		error(0, NULL);
	
// 	path = ft_strjoin(chemin, cmd[0]);
	
// 	if (!path || access(path, F_OK & X_OK) != 0)
// 	{
// 		i = 0;
// 		error(2, cmd[0]);
// 		while (cmd[i])
// 			free(cmd[i++]);
// 		free(cmd);
// 		free(path);
// 		exit(EXIT_FAILURE);
// 	}

// 	// write(2, path, ft));
// 	// write(2,"\n\n\n", 3);
	
// 	// // display_env(cmd);
// 	// exit(0);

// 	final_execute(path, cmd, envp);
// 	return ;
// }

// void	final_execute(char *path, char **cmd, char **envp)
// {
// 	int	i;

// 	i = 0;	
	
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		while (cmd[i])
// 			free(cmd[i++]);
// 		free(cmd);
// 		free(path);
// 		error(0, NULL);
// 	}
// }