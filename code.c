/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:20:17 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 11:15:46 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_tok *head)
{
	t_tok	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	print_tab_tok(t_tok *tok)
{
	t_tok	*tmp;

	if (!tok)
		return ;
	tmp = tok;
	while (tmp)
	{
		printf("%s = %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*env;
	t_tok	*lst;
	t_data	*d; // General structure

	(void)av;
	d = NULL;
	d = init_data(d, envp);
//****************************************************	
	int		i = 0;
	while (d->paths[i])
	{
		printf("d->paths[%d] = %s\n", i, d->paths[i]);
		i++;
	}
//****************************************************	
	
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
			lst = is_token(input, lst);
			exec_command(d, input); // command exec function
			if (check(lst) == true && parsing(input) == 1)
			{
				ret_value(env, lst);
				print_no_quotes(input); // Attention, cette fonction genere un retour a la ligne '\n'
				free_list(lst);
				free(input);
			}
		}
		free(env);
		free(d);
	}
}
