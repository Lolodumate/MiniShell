/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:36:59 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 03:43:09 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[j] = s[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
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
	if (!new)
	{
		perror("Malloc failed");
		return (NULL);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}
