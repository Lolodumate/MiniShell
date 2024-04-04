/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:20:54 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 08:24:01 by abdmessa         ###   ########.fr       */
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

// remplacer la chaîne dans la liste pour les value plus tard
void	replace_str_in_list(t_tok *lst, char *new_str)
{
	free(lst->str);
	lst->str = new_str;
}

// passage à la liste suivante
t_tok	*handle_next_list(t_tok *lst)
{
	if (!lst->next)
		return (NULL);
	return (lst->next);
}

// fonction principale de lexpand AKA la norminette
void	process_var_expansion(t_env *env, t_tok *lst)
{
	char	var_name[1000];
	t_var_expand	var;

	var.var_start = find_next_var(lst->str);
	while (var.var_start && *var.var_start)
	{
		if ((!*(var.var_start + 1) || *(var.var_start + 1) == ' ') && *var.var_start == '$')
		{
			lst = handle_next_list(lst);
			if (!lst)
				return ;
			var.var_start = find_next_var(lst->str);
			if (!var.var_start)
				break ;
		}
		extract_var_name(var.var_start, var_name);
		var.var_value = find_var_value(env, var_name);
		if (!var.var_value)
			var.var_value = "";
		var.var_end = var.var_start + ft_strlen(var_name) + 1;
		var.new_str = construct_new_str(lst->str, var.var_start, var.var_end, var.var_value);
		replace_str_in_list(lst, var.new_str);
		var.var_start = find_next_var(lst->str);
	}
}

void	expand(t_env *env, t_tok *lst)
{
	t_tok	*tmp_lst;

	tmp_lst = lst;
	while (tmp_lst)
	{
		process_var_expansion(env, tmp_lst);
		tmp_lst = tmp_lst->next;
	}
}
