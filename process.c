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

// cmd correspond a la commande a executer (premier token WORD qui suit immediatement le token PIPE)
// ATTENTION : cmd peut inclure un nombre variable d'options (par ex. : ls -l -a)
void	child_process(char *cmd, int **end, int i, char **envp)
{
/*	int		fd;

	fd = 0;
	if (redir(cmd))
	{
		fd = open(cmd, O_RDONLY, 0644);
		if (fd == -1)
			exit_error("child fd in");
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_error("child dup2 in");
	}
*/
//	printf("child process : i = %d\n", i);	
	if (dup2(end[i][1], STDOUT_FILENO) == -1)
		exit_error("child dup2 out");
	close_pipe(end, i, 1);
	close_pipe(end, i, 0);
//	if (redir(cmd))
//		close(fd);
	exec_command(cmd, envp);
}

void	parent_process(int **end, int i, int nb_pipe)
{
/*	int		fd;

	fd = 0;
	if (redir(cmd))
	{
		fd = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_error("parent fd out");
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_error("parent dup2 out");
	}
	else*/ 
//	printf("parent process : i = %d\n", i);	
	if (i < nb_pipe)
	{
		if (dup2(end[i][0], STDIN_FILENO) == -1)
			exit_error("parent dup2 in");
		close_pipe(end, i, 0);
		close_pipe(end, i, 1);
	}
//	if (redir(cmd))
//		close(fd);
}
