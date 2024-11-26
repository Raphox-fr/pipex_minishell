/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:22:44 by raphox            #+#    #+#             */
/*   Updated: 2024/11/26 19:37:44 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void execute(t_data_rule data, char **envp, int *p_fd)
{
	char *pathname;
    char **cmd = build_command(data);

	pathname = find_path(cmd[0], envp);
	close(p_fd[0]);
    close(p_fd[1]);


    if (!cmd[0])
    {
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_FAILURE);
    }

	
	if (pathname == NULL && check_if_in_builtins(data, envp) == 0)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ":", 1);
		write(2, " command not found\n", 19);
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_FAILURE);
	}
	
	
    if (data.oper != NULL)
    {
        handle_redirection(data);
    }

	if (check_if_in_builtins(data, envp) == 1)
	{
		// write(1, "coucou", 6); 
		exec_builtins(data, envp);
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (check_if_in_builtins(data, envp) == -1)
	{
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (execve(pathname, cmd, envp) == -1)
	{

		free_env(cmd);
		free(pathname);

		free_env(envp);
		envp = NULL;

		perror("execve");
		exit(EXIT_FAILURE);
    }
	exit(EXIT_SUCCESS);
}

void execution_process(t_data_rule data, char **env, int *input_fd, int *p_fd, int is_last_cmd)
{
    if (input_fd != NULL && *input_fd != -1)
    {
        dup2(*input_fd, STDIN_FILENO);
        close(*input_fd);
    }

    if (!is_last_cmd) // pas la derniere commande // est different de 0 je crois
    {
        close(p_fd[0]);
        dup2(p_fd[1], STDOUT_FILENO);
        close(p_fd[1]);
	}
    execute(data, env, p_fd);
}

void second_process(int *input_fd, int *p_fd, int is_last_cmd)
{
    if (input_fd != NULL && *input_fd != -1)
    {
        close(*input_fd);
    }
    if (!is_last_cmd) // pas la derniere commande // est different de 0 je crois
    {
        close(p_fd[1]);
        *input_fd = p_fd[0];
    }
    else
    {
        close(p_fd[0]);
        close(p_fd[1]);
    }
}

void do_pipe(t_data_rule data, char **env, int *input_fd, int is_last_cmd)
{
    pid_t pid;
    int p_fd[2];

    if (pipe(p_fd) == -1)
    {
        exit(1);
    }

    pid = fork(); // dedoublement du code
    if (pid == -1)
    {
        exit(1);
    }
    if (pid == 0)
    {
		execution_process(data, env, input_fd, p_fd, is_last_cmd); // enfant
    }
    else // pid different de 0
    {
        second_process(input_fd, p_fd, is_last_cmd); // parents
    }
	
}

char **pipex(t_data_rule *data, int num_commands, char **envv)
{
    int input_fd = -1;
    int i = 0;

	if (num_commands == 0)
		return (envv);
	
    while (i < num_commands)
    {
        int is_last_command;

        if (i == num_commands - 1)
            is_last_command = 1;
        else
            is_last_command = 0;

		if (check_if_in_builtins(data[i], envv) == -1 && data[i].pipe == false)
		{
			envv = exec_builtins(data[i], envv);
		}
        do_pipe(data[i], envv, &input_fd, is_last_command);
        i++;
    }
    wait_for_children();
    return (envv);
}





