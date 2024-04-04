/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:05:14 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 15:26:37 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour trouver la prochaine variable dans la chaîne
char	*find_next_var(char *str)
{
	return (ft_strchr(str, '$'));
}

// Fonction pour extraire le nom de la variable
void	extract_var_name(char *var_start, char *var_name)
{
	char	*var_end;
	
	if (var_start[0] == '$' && var_start[1] == '?')
		printf("je suis une exit \n");
	var_end = var_start + 1;	
	while (isalnum(*var_end) || *var_end == '_')
		var_end++;
	strncpy(var_name, var_start + 1, var_end - var_start - 1);
	var_name[var_end - var_start - 1] = '\0';
}

// Fonction pour rechercher la valeur de la variable dans l'environnement
char	*find_var_value(t_env *env, char *var_name)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, var_name) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

// Fonction pour construire la nouvelle chaîne avec la valeur de la variable
char	*construct_new_str(char *old_str, char *var_start, char *var_end,
		char *var_value)
{
	int new_str_len;
	char *new_str;

	new_str_len = ft_strlen(old_str) - (var_end - var_start) + ft_strlen(var_value);
	new_str = malloc(new_str_len + 1);
	if (new_str)
	{
		strncpy(new_str, old_str, var_start - old_str);
		new_str[var_start - old_str] = '\0';
		strcat(new_str, var_value);
		strcat(new_str, var_end);
	}
	return (new_str);
}
