/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:17:46 by raphox            #+#    #+#             */
/*   Updated: 2024/12/18 16:00:00 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

static void print_request(t_data_rule *request)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (!request)
		return ;
	while (k < request[0].nb_command) {
		i = 0;
		printf("-----------------\n");
		printf("command : %s\n", request[k].command);
		printf("nbr_arg : %d\n", request[k].nbr_args);
		if (request[k].options)
		{
			i = 0;
			while (request[k].options[i])
			{
				printf("option[%d] : %s\n", i, request[k].options[i]);
				i++;
			}
		}
		
		if (request[k].arguments)
		{
			i = 0;
			while(i < request[k].nbr_args)
			{
				printf("arg[%d] : |%s|\n", i, request[k].arguments[i]);
				i++;
			}
		}
		if (request[k].out)
		{
			i = 0;
			printf("nb_dir : %d\n", request[k].nb_rdir);
			while(request[k].out[i] && i < request[k].nb_rdir)
			{
				printf("out : %s\n", request[k].out[i]);
				i++;
			}
		}
		printf("input : %s\n", request[k].input);
		printf("nb_rdir : %d\n", request[k].nb_rdir);
		if (request[k].oper && i <= request[k].nb_rdir)
		{
			i = 0;
			while (request[k].oper[i])
			{
				printf("oper : %c\n", request[k].oper[i]);
				i++;
			}
		}
		printf("pipe : %B\n", request[k].pipe);
		printf("nb_command : %d\n", request[k].nb_command);
		k++;
	}
	printf("------------------------------------------\n");

}

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
}


int main(int argc, char **argv, char **envp)
{
	char	*rule;
	t_erreur	err;
	t_data_rule *request;
	char **envv;
	t_var	*var;
	(void)argc;
	(void)argv;

	signal(SIGINT, signal_treatment);
	signal(SIGQUIT, signal_treatment);
	envv = ft_strdup_env(envp);
	var = NULL;
	while (42)
	{
		err.error_code = -1;
		rule = NULL;
		rule = readline(PROMPT);
		if (rule == NULL)
			free_all(var, envv, rule, 3);
		if (rule != NULL)
		{
			if (ft_strncmp(rule, "exit", 4) == 0)
				break ;
//			if (ft_strncmp(rule, "var", 3) == 0)
//				print_var(var);
			add_history(rule);
			request = parsing(rule, &var, &err);
			if (!request)
				print_parsing_error(err);
			else {
				print_request(request);
				envv = pipex(request, request->nb_command, envv);
			}
			killer_request(request);
			free(rule);
		}
	}
	free_all(var, envv, rule, 0);
	return 0;
}

// S occuper du no such fill or directory de cd

// cd ../../Documents/GNL/gnlTester/


	// t_data_rule export;
	// char *tab_export[2] = {"var1=bonjourourour", NULL};
	// export.command = "export";
    // export.options = NULL;
    // export.arguments = tab_export;
	// export.input = NULL;
	// export.out = tab_export;
	// export.oper = NULL;
	// export.nbr_args = 1;
    // export.dir_path = NULL;
	// export.nb_command = 0;
    // export.pipe = false;

	// char **cmd;
	// cmd = build_command(export);

	// int i;
	// i = 0;

	// while (cmd[i])
	// {
	// 	printf("%s\n", cmd[i]);
	// 	i++;
	// }
	
	// free_env(envv);
	// free_command(cmd);
	// return (0);

	// rule = find_path("la", envv);
	// printf("%s", rule);
	// free_env(envv);
	// free(rule);
// cat | cat | ls



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

	// t_data_rule export;
	// 	char *tab_export[2] = {"var1=bonjourourour", NULL};
	// export.command = "export";
    // export.options = NULL;
    // export.arguments = NULL;
	// export.input = NULL;
	// export.out = tab_export;
	// export.oper = NULL;
	// export.nbr_args = 1;
    // export.dir_path = NULL;
	// export.nb_command = 0;
    // export.pipe = false;

	// t_data_rule ls;
	// char *tab_options[3] = {"-l", 0, 0};
	// char tab_oper_ls[4] = {'r', '>', 'r', 0};
	// char *tab_out_ls[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // ls.command = "ls";
    // ls.options = tab_options;
    // ls.arguments = NULL;
	// ls.input = NULL;
	// ls.out = NULL ;
	// // ls.out = tab_out_ls;
	// ls.oper = NULL;
	// // ls.oper = tab_oper_ls;
	// ls.nbr_args = 0;
    // ls.dir_path = NULL;
    // ls.pipe = false;

	// 	t_data_rule fin;
	// // char *tab_options_export[3] = {"-l", 0, 0};
	// // char tab_oper_cast[4] = {'r', '>', 'r', 0};
	// // char *tab_out_cast[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // fin.command = NULL;
    // fin.options = NULL;
    // fin.arguments = NULL;
	// fin.input = NULL;
	// fin.out = NULL ;
	// // fin.out = tab_out_fin;
	// fin.oper = NULL;
	// // fin.oper = tab_oper_fin;
	// fin.nbr_args = 0;
    // fin.dir_path = NULL;
    // fin.pipe = false;

    		// t_data_rule export_boy[2] = {export, fin};
    		// t_data_rule ls_boy[2] = {ls, fin};
			
			
			// envv = pipex(export_boy, count_data(export_boy), envv);
			// display_env(envv);
			
			// envv = pipex(ls_boy, count_data(ls_boy), envv);




	// 	t_data_rule ls;
	// char *tab_options[3] = {"-l", 0, 0};
	// char tab_oper_ls[4] = {'r', '>', 'r', 0};
	// char *tab_out_ls[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // ls.command = "ls";
    // ls.options = tab_options;
    // ls.arguments = NULL;
	// ls.input = NULL;
	// ls.out = NULL ;
	// // ls.out = tab_out_ls;
	// ls.oper = NULL;
	// // ls.oper = tab_oper_ls;
	// ls.nbr_args = 0;
    // ls.dir_path = NULL;
    // ls.pipe = false;

	// t_data_rule cat;
	// char *tab_options_cat[3] = {"-l", 0, 0};
	// char tab_oper_cast[4] = {'r', '>', 'r', 0};
	// char *tab_out_cast[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // cat.command = "cat";
    // cat.options = NULL;
    // cat.arguments = NULL;
	// cat.input = NULL;
	// cat.out = NULL ;
	// // cat.out = tab_out_cat;
	// cat.oper = NULL;
	// // cat.oper = tab_oper_cat;
	// cat.nbr_args = 0;
    // cat.dir_path = NULL;
    // cat.pipe = true;

	// t_data_rule fin;
	// // char *tab_options_cat[3] = {"-l", 0, 0};
	// // char tab_oper_cast[4] = {'r', '>', 'r', 0};
	// // char *tab_out_cast[4] = {"x.txt", "y.txt", "z.txt", NULL};
    // fin.command = NULL;
    // fin.options = NULL;
    // fin.arguments = NULL;
	// fin.input = NULL;
	// fin.out = NULL ;
	// // fin.out = tab_out_fin;
	// fin.oper = NULL;
	// // fin.oper = tab_oper_fin;
	// fin.nbr_args = 0;
    // fin.dir_path = NULL;
    // fin.pipe = false;

























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
