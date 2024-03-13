/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:31:25 by laroges           #+#    #+#             */
/*   Updated: 2024/03/13 16:05:48 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (input == NULL || !ft_strncmp(input, "exit", 4))
			break ;
		if (ft_strlen(input) > 0)
			add_history(input);
		exec_command(input);
	}
}
