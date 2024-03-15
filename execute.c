/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/15 12:19:58 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char *input)
{
	int		i;
	int		pid;
	char    **cmd;

	cmd = ft_split(input, ' ');
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (access(cmd[0], F_OK) == 0)
			execve(cmd[0], cmd, NULL);
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	free_str(cmd);
}
