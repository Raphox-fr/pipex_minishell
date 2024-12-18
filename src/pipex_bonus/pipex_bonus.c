/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:22:44 by raphox            #+#    #+#             */
/*   Updated: 2024/12/18 16:56:54 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void execute(t_data_rule data, char **envp, int *p_fd, int *tab_heredoc)
{
	char *pathname;
    char **cmd;

	// exit(EXIT_FAILURE);
	
	cmd = build_execution(data);

	close(p_fd[0]);
	close(p_fd[1]);
	
	if (tab_heredoc != NULL)
	{
		free(tab_heredoc);
	}
	
    if (cmd == NULL) // Verification "command chemin" bon quand donnee
    {
		write(2, "-3\n", 2);
		display_error(data.command, NULL, errno, data.arguments);
		free_env(envp);
		envp = NULL;
		exit(EXIT_FAILURE);
    }


	if (data.oper != NULL && (handle_redirection(data) == -1)) // Execution redirections
	{
			free_env(cmd);

			free_env(envp);
			envp = NULL;
			exit(EXIT_FAILURE);
	}

	pathname = find_path(cmd[0], envp);
    if (pathname == NULL && check_if_in_builtins(data, envp) == 0) // Verification commande existante
    {
		write(2, "-1\n", 2);
		display_error(cmd[0], "cmd not found", 0, NULL);
		free(pathname);
		free_env(cmd);
		free_env(envp);
		envp = NULL;
		exit(EXIT_FAILURE);
    }

	
	if (check_if_in_builtins(data, envp) == 1) // Execution builtins echo env pwd
	{
		write(2, "2\n", 2);
		exec_builtins(data, envp);
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (check_if_in_builtins(data, envp) == -1) // Exit d'execution builtins cd export unset
	{
		write(2, "3\n", 2);
		// write(2,"dans enfant\n", 12);
		free_env(cmd);
		free(pathname);
		free_env(envp);
		envp = NULL;
		exit(EXIT_SUCCESS);
	}
	
	else if (execve(pathname, cmd, envp) == -1)
	{
		write(2, "5\n", 2);
		free_env(cmd);
		free(pathname);

		free_env(envp);
		envp = NULL;

		perror("execve");
		exit(EXIT_FAILURE);
    }
	exit(EXIT_SUCCESS);
}

void execution_process(t_data_rule data, char **env, int *input_fd, int *p_fd, int is_last_cmd, int fd_heredocs, int *tab_heredoc)
{
	if (fd_heredocs != -1)
	{
		dup2(fd_heredocs, STDIN_FILENO);
        close(fd_heredocs);
		close(*input_fd);
	}
    
	else if (input_fd != NULL && *input_fd != -1)
    {
		dup2(*input_fd, STDIN_FILENO);
        close(*input_fd);
		close(fd_heredocs);
    }
    if (is_last_cmd != 1) // pas la derniere commande // est different de 0 je crois
    {
        close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
        close(p_fd[1]);
	}
    execute(data, env, p_fd, tab_heredoc);
}

void second_process(int *input_fd, int *p_fd, int is_last_cmd)
{
    if (input_fd != NULL && *input_fd != -1)
    {
        close(*input_fd);
    }
    if (is_last_cmd != 1) 
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

void do_pipe(t_data_rule data, char **env, int *input_fd, int is_last_cmd, int fd_heredocs, int *tab_heredoc)
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
		execution_process(data, env, input_fd, p_fd, is_last_cmd, fd_heredocs, tab_heredoc); // enfant
    }
    else // pid different de 0
    {
		if (data.oper != NULL && data.oper[0] == 'h')
			waitpid(pid, NULL, 0);
        second_process(input_fd, p_fd, is_last_cmd); // parents
    }
	
}

char **pipex(t_data_rule *data, int num_commands, char **envv)
{
    int i = 0;
    int input_fd = -1;

	int *tab_heredoc;
	
	tab_heredoc = prepare_heredocs(data, num_commands);
	if (tab_heredoc == NULL)
		return (envv);

	if (num_commands == 0)
		return (envv);
	
    while (i < num_commands)
    {
        int is_last_command;

        if (i == num_commands - 1)
            is_last_command = 1;
        else
            is_last_command = 0;

		if (check_if_in_builtins(data[i], envv) == -1) // Check if in  builtins cd export unset
		{
			if (check_redirections(data[i]) == 0) // Verification redirections de ces builtins
			{
				envv = exec_builtins(data[i], envv);
			}
		}
        do_pipe(data[i], envv, &input_fd, is_last_command, tab_heredoc[i], tab_heredoc);
        i++;
    }
    wait_for_children();
	free(tab_heredoc);
    return (envv);
}


int *prepare_heredocs(t_data_rule *data, int num_commands)
{
    int *tab_heredoc;
    int i;

    tab_heredoc = malloc(sizeof(int) * num_commands);
    if (!tab_heredoc)
    {
        perror("malloc");
        return (NULL);
    }

    i = 0;
    while (i < num_commands)
    {
        if (data[i].oper != NULL && data[i].oper[0] == 'h') // Si heredoc détecté
        {
            tab_heredoc[i] = handle_heredoc(data[i].input);
            
			if (tab_heredoc[i] == -1) // Vérifier les erreurs de handle_heredoc
            {
                write(2, "Erreur : Heredoc échoué\n", 24);
                free(tab_heredoc);
                return (NULL);
            }
        }
        else
        {
            tab_heredoc[i] = -1; // Pas de heredoc pour cette commande
        }
        i++;
    }
    return (tab_heredoc);
}

// env > z.txt | cat << l
// cd dfsgfdsg > zzzzz.txt
// cat za.txt > zzzzz.txt 
// cat << z | grep "o
// echo "bonjouRRRRRRRRRRRRRRR" | cat << fin | ls
// echo "bonjouRRRRRRRRRRRRRRR" > AAA.txt | cat << fin | ls
// 