/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/27 04:41:11 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_command(t_data *d, char **input)
{
	char	*cmd;

	cmd = NULL;
	while (input[d->i] && input[d->i] != "|")
	{
		cmd = ft_strjoin(cmd, input[d->i]);
		cmd = ft_strjoin(cmd, " ");
		d->i++;
	}
	return (cmd);
}

void	exec_command(t_data *d, char *input)
{
	pid_t		pid;
	int		status;
	char    **cmd;
	char	*try_path;

	cmd = ft_split(input, ' ');
	try_path = find_the_right_path(d, input);
	if (try_path == NULL)
		exit_error("command not found");
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
			exit_error("wait");
		if (WIFEXITED(status))
			WTERMSIG(status);
	}
	free_str(try_path);
	free_double_str(cmd);
}

char	*find_the_right_path(t_data *d, char *input)
{
	int		i;
	char	**cmd;
	char	*try_path;

	i = 0;
	cmd = ft_split(input, ' ');
	try_path = NULL;
	while (d->paths[i])
	{
		try_path = ft_strjoin(d->paths[i], cmd[0]);
		if (access(try_path, F_OK) == 0)
			break ;
		free(try_path);
		try_path = NULL;
		i++;
	}
	return (try_path);
}
