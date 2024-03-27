/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:15 by laroges           #+#    #+#             */
/*   Updated: 2024/03/27 02:55:03 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_double_str(char **str)
{
	int             i;

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

void	free_data(t_data *d)
{
	if (!d)
		return ;
	if (d->paths)
		free(d->paths);
	free(d);
}

void	exit_error(const char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
