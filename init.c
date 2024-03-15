/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:08:25 by laroges           #+#    #+#             */
/*   Updated: 2024/03/15 17:53:27 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(t_data *d, char **envp)
{
	d = malloc(sizeof(t_data));
	if (!d)
		exit(EXIT_FAILURE);
	d->paths = get_paths(envp);
	return (d);
}
