/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:36:59 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 08:04:21 by abdmessa         ###   ########.fr       */
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

void	ft_lstadd_back_tok(t_tok **lst, t_tok *new)
{
	t_tok	*current;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while ((*current).next)
			current = (*current).next;
		(*current).next = new;
	}
}

t_tok	*ft_lstnew_tok(char *str, int type)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	new->str = ft_calloc(sizeof(char), ft_strlen(str)+1);
	if (!new)
	{
		perror("ft_calloc failed");
		return (NULL);
	}
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}
/* Commentaire Laurent : 
 * 
 * 	Fonction ft_lstnew_tok :
 * 	- La protection de 'new' doit etre faite immediatement apres le malloc sinon le programme risque de crasher sur 'new->str'.
 *	- Il faut egalement proteger le ft_calloc sur new->str.
 *
 * 	Comme ceci :
 *

t_tok   *ft_lstnew_tok(char *str, int type)
{
        t_tok   *new;

        new = malloc(sizeof(t_tok));
        if (!new)                                                                                                                           {
                perror("malloc failed");
                return (NULL);
        }
        new->str = ft_calloc(sizeof(char), ft_strlen(str)+1);
	if (!new->str)
	{
                perror("ft_calloc failed");
                return (NULL);
	}
        new->str = ft_strdup(str);
        new->type = type;
        new->next = NULL;
        return (new);
}

 *
 *
 */
