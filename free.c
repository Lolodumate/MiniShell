/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:15 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 16:47:20 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_tok *lst)
{
	t_tok	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_double_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_end(int **end, int n)
{
	int             i;

	i = -1;
	if (!end)
		return ;
	while (++i < n)
		free(end[i]);
	free(end);
}
