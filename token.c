/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:52 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 08:02:36 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour traiter les opérateurs de redirection
void	process_redirect_operators(t_tok **new, char *input, int *i)
{
	if (input[*i] == '|')
	{
		ft_lstadd_back_tok(new, ft_lstnew_tok("|", PIPE));
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		ft_lstadd_back_tok(new, ft_lstnew_tok(">>", DSUP));
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		ft_lstadd_back_tok(new, ft_lstnew_tok("<<", DINF));
		*i += 2;
	}
	else if (input[*i] == '<')
	{
		ft_lstadd_back_tok(new, ft_lstnew_tok("<", INF));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		ft_lstadd_back_tok(new, ft_lstnew_tok(">", SUP));
		(*i)++;
	}
}

// Fonction pour traiter les mots
void	process_words(t_tok **new, char *input, int *i)
{
	char	*word;
	int		j;

	word = ft_calloc(sizeof(char), (count_len_tok(input + *i)) + 1);
	if (!word)
		return ;
	j = 0;
	while (input[*i] && !ft_separator(input[*i]))
	{
		word[j++] = input[(*i)++];
	}
	ft_lstadd_back_tok(new, ft_lstnew_tok(word, WORD));
	free(word);
}

// Fonction principale pour l'analyse
t_tok	*is_token(char *input)
{
	t_tok	*new;
	int		i;

	new = NULL;
	i = 0;
	input = tok_quote(input);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			process_redirect_operators(&new, input, &i);
		}
		else if (!ft_separator(input[i]))
		{
			process_words(&new, input, &i);
		}
		else
		{
			i++;
		}
	}
	return (new);
}
