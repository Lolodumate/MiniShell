/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:35:03 by laroges           #+#    #+#             */
/*   Updated: 2024/03/15 17:54:50 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data *d;
	(void)argc;
	(void)argv;

	d = NULL;
	d = init_data(d, envp);
	prompt(d, argc, argv, envp);
	free_data(d);
	return (0);
}
