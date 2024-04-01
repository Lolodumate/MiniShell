/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:48:13 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 17:07:41 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

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
		if (input[i] == '|')
			n++;
	}
	return (n);
}

// Si le token est un '|' alors on ouvre un pipe avec cette fonction
int	init_pipe(int **end, int i)
{
	if (pipe(end[i]) == -1)
	{
		// Ajouter fonction de liberation de la memoire avant de quitter
		exit_error("pipe");
	}
	return (EXIT_SUCCESS);
}

// Multiple pipes function (version char **)
void	exec_pipe(char **input, char **envp, int nb_pipe) // nb_pipe = nombre de pipes dans la ligne de commande
{
	int		i;
	int		**end;
	int		status;
	pid_t		pid[1024];

	i = -1;
	end = NULL;
	if (nb_pipe > 0)
	{
		end = (int **)malloc(sizeof(int *) * nb_pipe);
		if (!end)
		{
			// Liberer la memoire
			exit_error("malloc int **");
		}
	}
	while ((++i < nb_pipe) && nb_pipe > 0)
	{
		end[i] = (int *)malloc(sizeof(int) * 2);
		if (!end[i])
		{
			// Liberer la memoire
			exit_error("malloc int *");
		}
//		printf("end[%d] OK\n", i);
		end[i][0] = 0;
		end[i][1] = 0;
//		printf("end[%d][%d] = %d\n", i, 0, end[i][0]);
//		printf("end[%d][%d] = %d\n", i, 1, end[i][1]);
	}
	i = -1;
	while (++i <= nb_pipe)
	{
		if (i < nb_pipe)
			init_pipe(end, i);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			// Nettoyer  la memoire
			exit_error("exec_pipe : pid");
		}
		else if (pid[i] == 0)
		{
			if (i < nb_pipe)
				child_process(input[i], end, i, envp);
			else
			{
//				printf("pid[%d] = %d\n", i, pid[i]);
//				printf("input[%d] = %s\n", i, input[i]);
				exec_command(input[i], envp);
			}
		}
		else
			parent_process(end, i, nb_pipe);
	}
	// Attendre la fin de tous les process enfants
	i = -1;
	while (++i <= nb_pipe)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			// Liberer la memoire
			exit_error("waitpid");
		}
		if (WIFEXITED(status))
			WTERMSIG(status);
	}
	free_end(end, nb_pipe);
}
