/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:52 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 08:06:38 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_tok(char *input)
{
	int	i;

	i = 0;
	while (input[i] && !ft_strchr("|>< \t", input[i]))
		i++;
	return (i);
}
//	invalide read of size  	test 12|01234
//	invalide write of size	test 12|01234

t_tok	*is_token(char *input, t_tok *token)
{
	t_tok	*new;
	int		i;
	int		j;
	char	*word;

	(void)token;
	i = 0;
	j = 0;
	word = NULL;
	new = NULL;
	while (input[i])
	{
		if (input[i] == '|')
			ft_lstadd_back_tok(&new, ft_lstnew_tok("|", PIPE));
		else if (input[i + 1] == '\0' && input[i] == '>' && input[i + 1] == '>')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok(">>", DSUP));
			i++;
		}
		else if (input[i + 1] == '\0' && input[i] == '<' && input[i + 1] == '<')
		{
			ft_lstadd_back_tok(&new, ft_lstnew_tok("<<", DINF));
			i++;
		}
		else if (input[i] == '<')
			ft_lstadd_back_tok(&new, ft_lstnew_tok("<", INF));
		else if (input[i] == '>')
			ft_lstadd_back_tok(&new, ft_lstnew_tok(">", SUP));
		if (input && !ft_strchr("|>< \t", input[i]))
		{
			word = malloc(sizeof(char) * count_len_tok(input) + 1);
			if (!word)
				return (NULL);
			j = 0;
			while (input[i] && !ft_strchr("|>< \t", input[i]))
				word[j++] = input[i++];
			word[j] = '\0';
			ft_lstadd_back_tok(&new, ft_lstnew_tok(word, WORD));
		}
		else
			i++;
	}
	return (new);
}
