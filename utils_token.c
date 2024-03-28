/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:36:59 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 05:45:36 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
