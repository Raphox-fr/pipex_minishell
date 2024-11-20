/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:08:20 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:11:07 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

void	fill_conv_rdir(t_data_rule *request, const int rdir, const int itr_oper)
{
	if (rdir == D_RDIR)
		request->oper[itr_oper] = 'r';
	if (rdir == RDIR)
		request->oper[itr_oper] = '>';
	if (rdir == D_INPUT)
		request->oper[itr_oper] = 'h';
	if (rdir == INPUT)
		request->oper[itr_oper] = '<';
}
