/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:20:54 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 09:52:38 by abdmessa         ###   ########.fr       */
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
// a gerer | pour linstant lexpand est provisoir
// si syntaxe mauvaise remplacer la key invalide par une chaine vide
// si apres le $ key correct strcat lst->value
// si key invalide strjoin chaine vide strdup "" tant que

char	*extract_var_name(char *str, int start_index)
{
	size_t	j;

	j = start_index + 1;
	while (str[j] && (isalnum(str[j]) || str[j] == '_' || str[j] == '$'))
	{
		j++;
	}
	if (j > strlen(str))
		return (NULL);
	return (strndup(str + start_index + 1, j - start_index - 1));
}

// cherche la value de la variable dans env
char	*find_env_value(t_env *env, char *var_name)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (strcmp(env_tmp->key, var_name) == 0)
		{
			return (strdup(env_tmp->value));
		}
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

void	replace_var_with_value(t_tok *lst_tmp, int start_index, int end_index,
		char *new_str)
{
	char	*prefix;
	char	*suffix;
	int		new_str_len;

	prefix = strndup(lst_tmp->str, start_index);
	suffix = strdup(lst_tmp->str + end_index);
	free(lst_tmp->str);
	new_str_len = strlen(new_str);
	lst_tmp->str = malloc(strlen(prefix) + new_str_len - 1 + strlen(suffix)
			+ 1);
	if (lst_tmp->str)
	{
		strcpy(lst_tmp->str, prefix);
		strcat(lst_tmp->str, new_str);
		strcat(lst_tmp->str, suffix - 1);
	}
	free(prefix);
	free(suffix);
}

// switch avc la value
void	update_token_values(t_env *env, t_tok *lst)
{
	t_tok	*lst_tmp;
	int		i;
	int		start_index;
	char	*var_name;
	char	*new_str;
	int		end_index;

	lst_tmp = lst;
	while (lst_tmp)
	{
		i = 0;
		while (lst_tmp->str[i])
		{
			if (lst_tmp->str[i] == '$')
			{
				start_index = i;
				var_name = extract_var_name(lst_tmp->str, start_index);
				if (var_name)
				{
					new_str = find_env_value(env, var_name);
					if (new_str)
					{
						end_index = start_index + strlen(var_name);
						replace_var_with_value(lst_tmp, start_index, end_index,
							new_str);
						free(new_str);
					}
					else
						replace_var_with_value(lst_tmp, start_index, start_index
							+ strlen(var_name) + 1, strdup(""));
					free(var_name);
					i = end_index;
				}
				else
				{
					replace_var_with_value(lst_tmp, start_index, start_index
						+ 1, strdup(""));
					i++;
				}
			}
			else
				i++;
		}
		lst_tmp = lst_tmp->next;
	}
}
