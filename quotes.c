/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:53:45 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 10:59:50 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"')
		{
			if (single_quotes % 2 == 0)
				double_quotes = !double_quotes;
		}
		else if (input[i] == '\'')
		{
			if (double_quotes % 2 == 0)
				single_quotes = !single_quotes;
		}
		i++;
	}
	if (double_quotes || single_quotes)
		return (0);
	return (1);
}

void	ignore_quotes(char *input, int *i)
{
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
	}
}

void	print_no_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				printf("%c", input[i++]);
		}
		i++;
	}
	printf("\n");
}

int	parsing(char *input)
{
	if (check_quotes(input) == 0)
		return (write(2, "\033[91m >> Minishell: Syntaxe error with quotes \n",
				48), 0);
	return (1);
}
