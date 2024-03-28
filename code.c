/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:20:17 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 16:43:50 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// affiche la string et le type de chaque maiilon d une liste chainees
void	print_tab_tok(t_tok *tok)
{
	t_tok	*tmp;

	if (!tok)
		return ;
	tmp = tok;
	printf ("========= token stocker avec type ============\n");
	while (tmp)
	{
		printf("[%s] =%d ", tmp->str, tmp->type);
		tmp = tmp->next;
	}
	printf("\n==============================================\n\n\n");
	
}

char	**convert_lst_to_tab(t_tok *lst)
{
	int		size;
	int		i;
	t_tok	*tmp;
	char	**tab;

	size = 0;
	i = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	tab = ft_calloc((size + 2), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		tab[i] = ft_calloc((strlen(tmp->str) + 2), sizeof(char));
		if (tab[i] == NULL)
			return (NULL);
		strcpy(tab[i], tmp->str);
		strcat(tab[i], " ");
		tmp = tmp->next;
		i++;
	}
	tab[size] = NULL;
	// free_list(lst);
	return (tab);
}

void	print_double_tab(char **str)
{
	printf("\n\n=============== pour exec ================\n");
	printf(" ici >  ");
	while (*str)
		printf("%s", *str++);
	printf("\n==========================================\n\n\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**paths;
	t_env	*env;
	t_tok	lst;
	char	**tab;

	(void)av;
	paths = get_paths(envp);
	if (ac == 1)
	{
		env = grab_env(envp);
		while (1)
		{
			input = readline(READLINE_PROMPT);
			if (!input)
				break ;
			if (!*input)
				continue ;
			if (input)
				add_history(input);
			lst = is_token(input);
			exec_command(input, paths);
			if (check(&lst) == true && parsing(input) == 1)
			{
				update_token_values(env, &lst);
				tab = convert_lst_to_tab(&lst);
				print_double_tab(tab);
				print_tab_tok(&lst);
				free(input);
			}
		}
		free(env);
	}
}
