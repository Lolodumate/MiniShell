/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:31:25 by laroges           #+#    #+#             */
/*   Updated: 2024/03/08 13:38:26 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (!input)
		{
			printf("Bye !\n");
			break ;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
	}
}
