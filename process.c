/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:56:58 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 17:09:24 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	child_process(t_cmd cmd, char *input, int *fd)
{
	close_pipe(cmd, cmd.p.i, 0);
	handle_dup2(cmd, cmd.p.end[cmd.p.i][1], STDOUT_FILENO);
	close_pipe(cmd, cmd.p.i, 1);
	handle_dup2(cmd, *fd, STDIN_FILENO);
	if (close(*fd) == -1)
		clean_exit(cmd, "close", EXIT_FAILURE);
	exec_command(cmd, input);
}

void	parent_process(t_cmd cmd, int *fd)
{
	close_pipe(cmd, cmd.p.i, 1);
	if (close(*fd) == -1)
		clean_exit(cmd, "close", EXIT_FAILURE);
	*fd = cmd.p.end[cmd.p.i][0];
}

void	last_child_process(t_cmd cmd, char *input, int fd)
{
	handle_dup2(cmd, fd, STDIN_FILENO);
	if (close(fd) == -1)
		clean_exit(cmd, "close", EXIT_FAILURE);
	exec_command(cmd, input);
}

void	last_parent_process(t_cmd cmd, int fd)
{
	if (close(fd) == -1)
		clean_exit(cmd, "close", EXIT_FAILURE);
}

