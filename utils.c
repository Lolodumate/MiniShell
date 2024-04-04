/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 07:55:34 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 08:16:41 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
	{
		perror("ft_calloc failed");
		return (NULL);
	}
	new->key = strdup(key);
	new->value = strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*current;

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

t_env	*create_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = ft_lstnew(key, value);
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	add_node_to_list(t_env **head, t_env **prev, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		(*prev)->next = new_node;
	}
	*prev = new_node;
}

//	fonction principal qui recup lenv
t_env	*grab_env(char **str)
{
	t_env	*head;
	t_env	*prev;
	int		i;
	char	*equal_sign;
	t_env	*new_node;

	head = NULL;
	prev = NULL;
	i = 0;
	while (str[i])
	{
		equal_sign = ft_strchr(str[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			new_node = create_new_node(str[i], equal_sign + 1);
			if (!new_node)
				return (NULL);
			add_node_to_list(&head, &prev, new_node);
		}
		i++;
	}
	return (head);
}
