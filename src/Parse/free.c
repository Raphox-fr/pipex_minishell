#include "minishell.h"
#include "../../includes/Parsing.h"

void	killer_request(t_data_rule *request)
{
	int i;
	int k;
	int nb_command;

	k = 0;
	if (!(request))
		return ;
	nb_command = request[0].nb_command;
	if (request[k].pipe)
	{
		while (k < nb_command) {
			i = 0;
			free((request[k]).command);
			if (request[k].nbr_args != 0)
			{
				while (i < request[k].nbr_args) {
					free(request[k].arguments[i]);
					i++;
				}
				free(request[k].arguments);
			}
			if (request[k].nb_rdir != 0)
			{
				i = 0;
				while(request[k].nb_rdir != 0)
					free(request[k].out[i++]);
				free(request[k].out);
				free(request[k].oper);
			}
			k++;
		}
	}
	free(request);
}