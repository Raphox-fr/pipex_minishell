#include "minishell.h"
#include "Parsing.h"

void	killer_request(t_data_rule **request)
{
	int i;
	int k;
	int nb_command;

	k = 0;
	if (!(request[k]))
		return ;
	nb_command = request[0]->nb_command;
	if (request[k]->nb_command > 0)
	{
		while (k < nb_command) {
			i = 0;
			free(request[k]->command);
			while (i < request[k]->nbr_args) {
				free(request[k]->arguments[i]);
				i++;
			}
			free(request[k]->arguments);
			k++;
		}
	}
	free(*request);
}
