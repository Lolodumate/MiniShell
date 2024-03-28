/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:52 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 05:52:58 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_separator(char c)
{
	if (c != '|' && c != '>' && c != '<' && c != ' ' && c != '\t')
		return (0);
	return (1);
}

// compte word pour la tokenisation
int	count_len_tok(char *input)
{
	int	i;

	i = 0;
	if (!input[i])
	{
		return (i);
	}
	while (input[i] && !ft_separator(input[i]))
		i++;
	return (i);
}

// passe les caracteres en negatif afin de skip les quotes
char	*tok_quote(char *input)
{
	int		i;
	char	c;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i];
			i++;
			while (input[i])
			{
				if (input[i] == c)
					break ;
				input[i] *= -1;
				i++;
			}
		}
	}
	return (input);
}

// fonction qui tokenise et range chaque type dans un maillon puis renvoie un liste de ses derniers

t_tok	is_token(char *input)
{
	t_tok	*new;
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	new = NULL;
	input = tok_quote(input);
	while (input[i])
	{
		if (input[i] == '|')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok("|", PIPE));
			i++;
		}
		else if (input[i] && input[i + 1] != '\0' && input[i] == '>' && input[i
				+ 1] == '>')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok(">>", DSUP));
			i += 2;
		}
		else if (input[i] && input[i + 1] != '\0' && input[i] == '<' && input[i
				+ 1] == '<')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok("<<", DINF));
			i += 2;
		}
		else if (input[i] == '<')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok("<", INF));
			i++;
		}
		else if (input[i] == '>')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok(">", SUP));
			i++;
		}
		else if (input[i] && !ft_separator(input[i]))
		{
			word = ft_calloc(sizeof(char), (count_len_tok(input + i)) + 1);
			if (!word)
				return (*new);
			j = 0;
			while (input[i] && !ft_separator(input[i]))
				word[j++] = input[i++];
			ft_lstadd_back_tok(&new, ft_lstnew_tok(word, WORD));
			free(word);
		}
		else
			i++;
	}
	return (*new);
}
