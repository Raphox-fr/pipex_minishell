/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:30:17 by raphox            #+#    #+#             */
/*   Updated: 2024/12/05 18:57:45 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char **cd(char *command, char **arguments, char **envp)
{
    char old_pwd[1024];
    int oldpwd_index;
    int pwd_index;
    char new_pwd[1024];
    char *resolved_path;
    char *home;
	DIR *dir;


	if (arguments != NULL)
	{
		dir = opendir(arguments[0]);
		if (dir == NULL)
		{
			display_error("cd", NULL, errno, arguments);
			closedir(dir);
			return(envp);
		}
	}
	
	getcwd(old_pwd, sizeof(old_pwd));

    if (command != NULL && arguments == NULL) // cd sans arguments (retourne au home directory)
    {
        home = getenv("HOME");
        chdir(home);
    }
    else if (command != NULL && arguments != NULL && strcmp(arguments[0], "..") == 0) // cd ..
    {
        chdir("..");
    }
    else if (command != NULL && arguments != NULL && arguments[0][0] == '/') // cd avec chemin absolu
    {
        chdir(arguments[0]);
    }
    else if (command != NULL && arguments != NULL && arguments[0][0] != '/') // cd avec chemin relatif
    {
        getcwd(new_pwd, sizeof(new_pwd));
        resolved_path = resolve_path(new_pwd, arguments[0]);		
        chdir(resolved_path);
        free(resolved_path);
    }

    oldpwd_index = find_in_envv(envp, "OLDPWD");
    pwd_index = find_in_envv(envp, "PWD");

	free(envp[oldpwd_index]);
    envp[oldpwd_index] = ft_strjoin("OLDPWD=", old_pwd, 0);
    
	getcwd(new_pwd, sizeof(new_pwd));
	
	free(envp[pwd_index]);
    envp[pwd_index] = ft_strjoin("PWD=", new_pwd, 0);

    return (envp);
}

char	*resolve_path(const char *cwd, const char *relative_path)
{
	char	*path;
	char	*resolved_path;
	size_t	cwd_len;
	size_t	rel_len;

	cwd_len = ft_strlen(cwd);
	rel_len = strlen(relative_path);
	path = malloc(cwd_len + rel_len + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, cwd, cwd_len + 1);
	ft_strlcat(path, "/", cwd_len + 2);
	ft_strlcat(path, relative_path, cwd_len + rel_len + 2);
	resolved_path = custom_realpath(path);
	free(path);
	return (resolved_path);
}

// 


void	parse_segments(const char *path, char **segments, int *segment_count)
{
	char	temp[1024];
	int		start;
	int		end;

	*segment_count = 0;
	ft_strlcpy(temp, path, sizeof(temp));
	start = 0;
	while (temp[start] != '\0')
	{
		while (temp[start] == '/')
			start++;
		if (temp[start] == '\0')
			break ;
		end = start;
		while (temp[end] != '/' && temp[end] != '\0')
			end++;
		temp[end] = '\0';
		if (ft_strncmp(temp + start, "..", 3) == 0)
		{
			if (*segment_count > 0)
			{
				free(segments[*segment_count - 1]);
				(*segment_count)--;
			}
		}
		else if (ft_strncmp(temp + start, ".", 2) != 0)
		{
			segments[*segment_count] = ft_strdup(temp + start);
			if (segments[*segment_count] == NULL)
			{
				int i = 0;
				while (i < *segment_count)
				{
					free(segments[i]);
					i++;
				}
				return ;
			}
			(*segment_count)++;
		}
		start = end + 1;
	}
}

char	*build_resolved_path(char **segments, int segment_count)
{
	char	*resolved_path;
	int		j;

	resolved_path = malloc(1024);
	if (!resolved_path)
	{
		int i = 0;
		while (i < segment_count)
		{
			free(segments[i]);
			i++;
		}
		return (NULL);
	}
	resolved_path[0] = '/';
	resolved_path[1] = '\0';
	j = 0;
	while (j < segment_count)
	{
		ft_strlcat(resolved_path, segments[j], 1024);
		if (j < segment_count - 1)
			ft_strlcat(resolved_path, "/", 1024);
		free(segments[j]);
		j++;
	}
	return (resolved_path);
}


char *custom_realpath(const char *path)
{
    char *segments[256];
    int segment_count;

    parse_segments(path, segments, &segment_count);
    return build_resolved_path(segments, segment_count);
}