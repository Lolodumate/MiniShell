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

int	close_pipe(int **end, int i, int j)
{
	if (!end)
		return (EXIT_FAILURE);
	if (close(end[i][j]) == -1)
		exit_error("close pipe");
	return (EXIT_SUCCESS);
}

bool	child_process(t_pipe p, char *cmd, char **envp, int *fd)
{
	close_pipe(p.end, p.i, 0);
	if (dup2(p.end[p.i][1], STDOUT_FILENO) == -1)
	{
		perror("child dup2 out");
		exit(EXIT_FAILURE);
	}
	close_pipe(p.end, p.i, 1);
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("child dup2 in");
		exit(EXIT_FAILURE);
	}
	close(*fd);
//	printf("child process : i = %d\n", p.i);	
//	printf("last child cmd : %s\n", cmd);
	if (!exec_command(cmd, envp))
	{
		perror("execve");
		exit(errno);
	}
	exit(EXIT_SUCCESS);
}

void	parent_process(t_pipe p, int *fd)
{
	close_pipe(p.end, p.i, 1);
	close(*fd);
	*fd = p.end[p.i][0];
//	printf("parent process : i = %d\n", p.i);	
}

void	last_child_process(char *cmd, char **envp, int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
//	printf("last child process : i\n");
//	printf("last child cmd : %s\n", cmd);
	exec_command(cmd, envp);
}

void	last_parent_process(int fd)
{
	close(fd);
//	printf("last parent process : i\n");	
}

