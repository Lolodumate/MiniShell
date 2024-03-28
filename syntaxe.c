/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:43:36 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/25 08:30:11 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_first_pipe(char *input)
{
	int	i;

	i = 0;
	if (!(input[i] == 32 || (input[i] == '\t')))
	{
		if (input[i] == '|')
			return (0);
	}
	else if (input[i] == 32 || (input[i] == '\t'))
	{
		while (input[i] == 32 || (input[i] == '\t'))
			i++;
		if (input[i] && input[i] == '|')
			return (0);
	}
	return (1);
}

int	syntax_last_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
		exit(1);
	while (input[i] && input[i + 1] != '\0')
		i++;
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (0);
	else if (input[i] == 32 || input[i] == '\t')
	{
		while (input[i] == 32 || input[i] == '\t')
			i--;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			return (0);
	}
	return (1);
}

int	chevron_space(char *input)
{
	int	i;

	i = 0;
	while (input[i++])
	{
		if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == 32
				|| input[i + 1] == '\t'))
		{
			i++;
			while (input[i] == 32 || input[i] == '\t')
				i++;
			if (input[i] == '<' || input[i] == '>')
				return (0);
		}
		else if ((input[i] == '<') || (input[i] == '>'
				&& (input[i + 1] == '>' || input[i + 1] == '>')))
		{
			i += 2;
			while (input[i] == 32 || input[i] == '\t')
				i++;
			if (input[i] == '<' || input[i] == '>')
				return (0);
		}
	}
	return (1);
}

int	chevron(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (input[i] && input[i + 2] != '\0' && (input[i] == '>'
					|| input[i] == '<') && (input[i + 1] == '>' || input[i
						+ 1] == '<') && (input[i + 2] == '>' || input[i
						+ 2] == '<'))
				return (0);
			if (input[i] && (input[i] == '>' || input[i] == '<'))
			{
				while ((input[i] && input[i] == 32) || input[i] == '\t')
					i++;
				if (input[i] != '>' || input[i] != '<' || input[i] != '|')
					return (1);
				else
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	syntax(char *input)
{
	int	i;

	i = 0;
	while (input[i++])
	{
		if (chevron(input) == 0 || chevron_space(input) == 0)
			return (0);
		ignore_quotes(input, &i);
		if (input[i] == '|')
		{
			while (input[i + 1] == 32 || input[i + 1] == '\t')
				i++;
			if (input[i + 1] == '|')
				return (0);
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			while (input[i + 1] == 32 || input[i + 1] == '\t')
				i++;
			if (input[i + 1] == '|')
				return (0);
		}
	}
	return (1);
}
