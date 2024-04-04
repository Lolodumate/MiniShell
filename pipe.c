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
 *
 *
 *    ** File descriptors debugging tools:
 *
 * 	- Open at exit:
 *       valgrind --trace-children=yes --track-fds=yes
 */

t_pipe	init_pipe_data(void)
{
	t_pipe	p;

	p.i = -1;
	p.nb_pipe = 0;
	p.end = NULL;
	p.cmd = NULL;
	return (p);
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

void	exec_no_pipe_command(char *cmd, char **envp)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		// Nettoyer la memoire
		exit_error("pid exec_no_pipe_command");
	}
	if (pid == 0)
		exec_command(cmd, envp);
	else
		wait(0);
}

// Multiple pipes function (version char **)
void	exec_pipe(char **input, char **envp, int nb_pipe) // nb_pipe = nombre de pipes dans la ligne de commande
{
	int		fd;
	int		status;
	pid_t		pid[1024];
	t_pipe		p;

	if (nb_pipe == 0)
		exec_no_pipe_command(input[0], envp);
	fd = dup(0);
	p = init_pipe_data();
	p.nb_pipe = nb_pipe;
	if (nb_pipe > 0)
	{
		p.end = (int **)malloc(sizeof(int *) * nb_pipe);
		if (!p.end)
		{
			// Liberer la memoire
			exit_error("malloc int **");
		}
	}
	while ((++p.i < p.nb_pipe) && nb_pipe > 0)
	{
		p.end[p.i] = (int *)malloc(sizeof(int) * 2);
		if (!p.end[p.i])
		{
			// Liberer la memoire
			exit_error("malloc int *");
		}
		p.end[p.i][0] = 0;
		p.end[p.i][1] = 0;
	}
	p.i = -1;
	while (++p.i <= nb_pipe)
	{
		if (p.i < nb_pipe)
			init_pipe(p.end, p.i);
		pid[p.i] = fork();
		if (pid[p.i] == -1)
		{
			// Nettoyer  la memoire
	//		free_end(end, nb_pipe);
			exit_error("exec_pipe : pid");
		}
		if (input[p.i + 1])
		{
			if (pid[p.i] == 0)
			{
				if (p.i < nb_pipe)
					child_process(p, input[p.i], envp, &fd);
				else
					exec_command(input[p.i], envp);
			}
			else
			{
				parent_process(p, &fd);
				waitpid(pid[p.i], &status, 0);
				if (WIFEXITED(status))
					WTERMSIG(status);
			}
		}
		else if (!input[p.i + 1])
		{
			if (pid[p.i] == 0)
				last_child_process(input[1], envp, fd);
			else
			{
				last_parent_process(fd);
				waitpid(pid[p.i], &status, 0);
				if (WIFEXITED(status))
					WTERMSIG(status);
			}
		}
	}
	free_end(p.end, nb_pipe);
}
