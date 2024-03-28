/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:20:54 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 11:16:11 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ret_value(t_env *env, t_tok *lst)
{
	t_env	*tmp_env;
	t_tok	*tmp_lst;
	int		i;

	i = 0;
	tmp_env = env;
	tmp_lst = lst;
	while (tmp_lst)
	{
		if (tmp_lst->str[i] && tmp_lst->str[i] != '$')
		{
			while (tmp_lst->str[i] && tmp_lst->str[i] != '$')
				i++;
		}
		if (tmp_lst->str[i] != '$' || tmp_lst->str[i] == '\0')
		{
			tmp_lst = tmp_lst->next;
			i = 0;
			continue ;
		}
		while (tmp_env)
		{
			if (tmp_lst->str[i] == '$')
				tmp_lst->str++;
			if (ft_strcmp(tmp_env->key, tmp_lst->str) == 0)
				printf("%s ", tmp_env->value);
			tmp_env = tmp_env->next;
		}
		tmp_env = env;
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}
