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
 * - Compter le nombre de pipes (int cmd.nb_pipe) dans l'cmd.input[p.i]
 * - Creer un process enfant qui va stocker le resultat du processus dans son fd.
 * - Le parent va alors lire le fd et ecrire le resultat dans son propre fd.
 * - On recommence le processus autant de fois que necessaire (cf. cmd.nb_pipe).
 *
 *
 *    ** File descriptors debugging tools:
 *
 * 	- Open at exit:
 *       valgrind --trace-children=yes --track-fds=yes
 */

// This function execute the right function following the command type
void	exec_input(t_cmd cmd, char *input)
{
	cmd.type_cmd = get_type_command(cmd, input);
	if (cmd.type_cmd == HEREDOC)
		run_heredoc(cmd.lst);
	else
		exec_pipe(cmd, input);
}

// Sub function for exec_input
static int	exec_pipe_in(t_cmd cmd, int fd, int status, pid_t *pid)
{
	if (pid[cmd.p.i] == 0)
	{
		if (cmd.p.i < cmd.nb_pipe)
			child_process(cmd, cmd.cmdin[cmd.p.i], &fd);
		else
			exec_single_command(cmd, cmd.cmdin[cmd.p.i]);
	}
	else
	{
		parent_process(cmd, &fd);
		waitpid(pid[cmd.p.i], &status, 0);
		if (WIFEXITED(status))
			WTERMSIG(status);
	}
	return (fd);
}

// Sub function for exec_input
static int	exec_pipe_out(t_cmd cmd, int fd, int status, pid_t *pid)
{
	if (pid[cmd.p.i] == 0)
	{
		if (cmd.nb_pipe == 0)
			last_child_process(cmd, cmd.cmdin[0], fd);
		else if (cmd.nb_pipe > 0)
			last_child_process(cmd, cmd.cmdin[cmd.p.i], fd);
	}
	else
	{
		last_parent_process(fd);
		waitpid(pid[cmd.p.i], &status, 0);
		if (WIFEXITED(status))
			WTERMSIG(status);
	}
	return (fd);
}

// Multiple pipes function (version char **)
//void	exec_pipe(t_tok *lst, char **input, char **envp, int cmd.nb_pipe) // cmd.nb_pipe = nombre de pipes dans la ligne de commande
void	exec_pipe(t_cmd cmd, char *input) // cmd.nb_pipe = nombre de pipes dans la ligne de commande
{
	int		fd;
	int		status;
	pid_t		pid[1024];

	fd = dup(0);
	status = 0;
	cmd = set_cmd(cmd, input);
	while (++cmd.p.i <= cmd.nb_pipe)
	{
		if (cmd.p.i < cmd.nb_pipe)
			init_pipe(cmd.p.end, cmd.p.i);
		pid[cmd.p.i] = fork();
		if (pid[cmd.p.i] == -1)
		{
			// Nettoyer  la memoire
			free_end(cmd.p.end, cmd.nb_pipe);
			exit_error("exec_pipe : pid");
		}
		if (cmd.cmdin[cmd.p.i + 1])
			fd = exec_pipe_in(cmd, fd, status, pid);
		else if (!cmd.cmdin[cmd.p.i + 1])
			fd = exec_pipe_out(cmd, fd, status, pid);
	}
	free_end(cmd.p.end, cmd.nb_pipe);
}
