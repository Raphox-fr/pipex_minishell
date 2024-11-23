/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:52:34 by raphox            #+#    #+#             */
/*   Updated: 2024/11/23 15:44:24 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_request(t_data_rule *request)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (k < request->nb_command) {
		i = 0;
		printf("-----------------\n");
		printf("command : %s\n", request[k].command);
		printf("nb_arg : %d\n", request[k].nbr_args);
		if (request[k].arguments)
		{
			while(i < request[k].nbr_args)
			{
				printf("arg[%d] : %s\n", i, request[k].arguments[i]);
				i++;
			}
		}
		if (request[k].options)
		{
			i = 0;
			while (request[k].options[i])
			{
				printf("option[%d] : %s\n", i, request[k].options[i]);
				i++;
			}
		}
		printf("input : %s\n", request[k].input);
		if (request[k].out)
		{
			i = 0;
			while(request[k].out[i])
			{
				printf("output : %s\n", request[k].out[i]);
				i++;
			}
		}
		if (request[k].oper)
		{
			i = 0;
			while (request[k].oper[i])
			{
				printf("oper : %c\n", request[k].oper[i]);
				i++;
			}
		}
		printf("pipe : %B\n", request[k].pipe);
		k++;
	}
	printf("-----------------\n");
}
	// t_data_rule ls;
	// char *tab_ls[0];
	// char tab_oper_ls[4] = {'r', '>', 'r', 0};
	// char *tab_out_ls[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // ls.command = "ls";
    // ls.options = NULL;
    // ls.arguments = NULL;
	// ls.input = NULL;
	// ls.out = NULL ;
	// // ls.out = tab_out_ls;
	// ls.oper = NULL;
	// // ls.oper = tab_oper_ls;
	// ls.nbr_args = 0;
    // ls.dir_path = NULL;
    // ls.pipe = false;
    // t_data_rule cmd_ls[1] = {ls};

static void signal_treatment(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("   \b\b");
	}
	else if (sig == EOF)
	{
		exit (3);
	}
}

int main(int argc, char **argv, char **envp)
{
	int count_cmd;
	char	*rule;
	t_erreur	err;
	t_data_rule *request;
	char **envv;
	(void)argc;
	(void)argv;

	signal(SIGINT, signal_treatment);
	signal(SIGQUIT, signal_treatment);
	envv = ft_strdup_env(envp);
	
	while (42)
	{
		err.error_code = -1;
		request = NULL;
		rule = NULL;
		rule = readline(PROMPT);
		if (rule == NULL)
			exit(3);
		if (rule != NULL)
		{
			if (ft_strncmp(rule, "exit", 4) == 0)
			{
				rl_clear_history();
				free(envv);
				free(rule);
				exit(1);
			}
			add_history(rule);
			request = parsing(rule, &err);
			count_cmd = count_data(request);
			print_request(request);
			envv = pipex(request, count_cmd, envv);
			if (!request)
				print_parsing_error(err);
			free(rule);
		}
	}
	free(envv);
	return 0;
}

int count_data(t_data_rule *la_struct)
{
	int i;
	i = 0;

	if (la_struct == NULL)
		return (0);

	while (la_struct[i].command != NULL)
	{
		i++;
	}
	return (i);
}



char **ft_strdup_env(char **envp)
{
    int i = 0;
    char **new_env;

    while (envp[i])
        i++;

    new_env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!new_env)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        if (!new_env[i])
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
        i++;
    }
	new_env[i] = NULL;
    return new_env;
}






























/*=======
    t_data_rule first;
    const char *tab1[4] = {"NULL", "NULL", "NULL", NULL};
    first.command = "ls";
    first.options = NULL;
    first.arguments = tab1;
    first.nbr_args = 3;
    first.dir_path = NULL;
    first.request = NULL;
    first.pipe = true;

    t_data_rule second;
    const char *tab2[3] = {"arg1", "arg2", NULL};
    second.command = "ls";
    second.options = NULL;
    second.arguments = tab2;
    second.nbr_args = 2;
    second.dir_path = NULL;
    second.request = NULL;
    second.pipe = true;

    t_data_rule third;
    const char *tab3[2] = {"argA", NULL};
    third.command = "ls";
    third.options = NULL;
    third.arguments = tab3;
    third.nbr_args = 1;
    third.dir_path = NULL;
    third.request = NULL;
    third.pipe = false;

    t_data_rule data[3] = {first, second, third};
	pipex

}*/




// ---------------------------------------------------------------------------------------------------


// int main(int argc, char **argv, char **envp)
// {

	
// 	pipex(argc, argv, envp);
	
// }







// int	main(int argc, char **argv, char **envp)
// {

	// char	*rule;
	// t_data_rule *request;

	// rule = NULL;

	// char **env;
	// env = envp;

// //---------------------------------
// 	t_data_rule first;

// 	const char *tab[4];
// 	tab[0] = "NULL";
// 	tab[1] = "NULL";
// 	tab[2] = "UNLL";
// 	tab[3] = NULL;

// 	// const char **tab;
// 	// *tab = NULL;

// 	first.command = "unset";
// 	first.options = NULL;
// 	first.arguments = NULL;
// // -----------------------------------------
// 	printf("FIRST ENV ----------------------------------------------------------------------------\n");
// 	display_env(envp);
// 	exec_builtins(first, envp);
// 	// display_env(envp);
// 	return (0);

//---------------------------------


	// rule = readline(PROMPT);
	// if (rule != NULL)
	// {
	// 	// request = parsing(rule);
	// 	exec_builtins(first, genv);
	// 	(void)request;
	// }
	// return (0);
// }
