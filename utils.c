/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 07:55:34 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 03:49:27 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("Malloc failed");
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s1;
	int		i;

	s1 = (char *)s;
	i = ft_strlen(s);
	if (c == '\0')
		return (&s1[i]);
	i = 0;
	while (s1[i])
	{
		if (s1[i] == (char)c)
			return (&s1[i]);
		i++;
	}
	return (0);
}

t_env	*grab_env(char **str)
{
	t_env	*head;
	t_env	*prev;
	t_env	*new_node;
	int		i;
	char	*equal_sign;

	head = NULL;
	prev = NULL;
	new_node = NULL;
	equal_sign = NULL;
	i = 0;
	while (str[i])
	{
		equal_sign = ft_strchr(str[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			new_node = ft_lstnew(str[i], equal_sign + 1);
			if (!new_node)
				return (NULL);
			if (!head)
				head = new_node;
			else
				prev->next = new_node;
			prev = new_node;
		}
		i++;
	}
	return (head);
}
