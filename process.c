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

void	close_pipe(int **end, int i, int j)
{
	if (!end)
		return ;
	if (close(end[i][j]) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

void	child_process(t_cmd cmd, char *input, int *fd)
{
	close_pipe(cmd.p.end, cmd.p.i, 0);
	if (dup2(cmd.p.end[cmd.p.i][1], STDOUT_FILENO) == -1)
	{
		perror("child dup2 out");
		exit(EXIT_FAILURE);
	}
	close_pipe(cmd.p.end, cmd.p.i, 1);
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("child dup2 in");
		exit(EXIT_FAILURE);
	}
	if (close(*fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	exec_command(cmd, input);
}

void	parent_process(t_cmd cmd, int *fd)
{
	close_pipe(cmd.p.end, cmd.p.i, 1);
	if (close(*fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	*fd = cmd.p.end[cmd.p.i][0];
}

void	last_child_process(t_cmd cmd, char *input, int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	exec_command(cmd, input);
}

void	last_parent_process(int fd)
{
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

