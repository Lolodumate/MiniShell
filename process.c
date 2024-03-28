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

// cmd correspond a la commande a executer (premier token WORD qui suit immediatement le token PIPE)
// ATTENTION : cmd peut inclure un nombre variable d'options (par ex. : ls -l -a)
void	child_process(char *cmd, int *end, char **envp)
{
	int		fd;

	fd = open(cmd, O_RDONLY, 0644);
	if (fd == -1)
		exit_error("child fd in");
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_error("child dup2 in");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		exit_error("child dup2 out");
	close(end[1]);
	close(end[0]);
	close(fd);
	exec_command(cmd, envp);
}

void	parent_process(char *cmd, int *end, char **envp)
{
	int		fd;

	fd = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error("parent fd out");
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_error("parent dup2 out");
	if (dup2(end[0], STDIN_FILENO) == -1)
		exit_error("parent dup2 in");
	close(end[1]);
	close(end[0]);
	close(fd);
	exec_command(cmd, envp);
}
