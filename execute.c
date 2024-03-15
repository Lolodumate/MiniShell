/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/15 17:58:36 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *d, char *input)
{
	int		pid;
	char    **cmd;
	char	*try_path;

	cmd = ft_split(input, ' ');
	try_path = NULL;
	try_path = find_the_right_path(d, input);
	if (try_path == NULL)
	{
		perror("command not found");
		exit(0);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execve(try_path, cmd, NULL);
	else
		wait(NULL);
	free_str(cmd);
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
