/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 16:26:14 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char *input, char **paths)
{
	pid_t		pid;
	int		status;
	char    **cmd;
	char	*try_path;

	cmd = ft_split(input, ' ');
	try_path = NULL;
	try_path = find_the_right_path(input, paths);
	if (try_path == NULL)
	{
		perror("command not found");
		return ;
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (execve(try_path, cmd, NULL) == -1)
		{
			free_str(try_path);
			perror("command not found");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			WTERMSIG(status);

	}
	free_str(try_path);
	free_double_str(cmd);
}

char	*find_the_right_path(char *input, char **paths)
{
	int		i;
	char	**cmd;
	char	*try_path;

	i = 0;
	cmd = ft_split(input, ' ');
	try_path = NULL;
	while (paths[i])
	{
		try_path = ft_strjoin(paths[i], cmd[0]);
		if (access(try_path, F_OK) == 0)
			break ;
		free(try_path);
		try_path = NULL;
		i++;
	}
	return (try_path);
}
