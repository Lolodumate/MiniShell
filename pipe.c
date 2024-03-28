/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:48:13 by laroges           #+#    #+#             */
/*   Updated: 2024/03/27 04:55:18 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Multipipes :
 * - Compter le nombre de pipes (int nb_pipe) dans l'input.
 * - Creer un process enfant qui va stocker le resultat du processus dans son fd.
 * - Le parent va alors lire le fd et ecrire le resultat dans son propre fd.
 * - On recommence le processus autant de fois que necessaire (cf. nb_pipe).
 */

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

// Comptage du nombre de pipes entres dans la chaine de caracteres input
int	nb_pipe(char *input)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (input[++i])
	{
		if (is_pipe(input[i]))
			n++;
	}
	return (n);
}

// Si le token est un '|' alors on ouvre un pipe avec cette fonction
int	*init_pipe(int end[2])
{
	if (pipe(end) == -1)
	{
		// Ajouter fonction de liberation de la memoire avant de quitter
		exit_error("pipe");
	}
	return (end);
}

void	exec_pipe(t_data *d, char *input)
{
	int		i;
	int		status;
	int		end[2];
	pid_t		pid;
	char	**cut_input;

	i = 0;
	status = 0;
	init_pipe(end);
	cut_input = ft_split(input, ' ');
	pid = fork();
	if (pid == -1)
	{
		// Ajouter fonction de liberation de la memoire avant de quitter
		exit_error("create process");
	}
	if (pid == 0)
		child_process(d, cut_input[0], end);
	else
		parent_process(d, cut_input[2], end);
	while (i < 2)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
