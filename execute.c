/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/13 16:45:55 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char **paths, char *input/*, t_data *data*/)
{
	int		i;
	char		**try_path;
	char    **cmd;

	cmd = ft_split(input, ' ');
	if (access(cmd[0], F_OK) == 0)
		execve(cmd[0], cmd, NULL);
	while (paths[i])
	{
		try_path = ft_strjoin(paths[i], cmd[0]);
		if (access(try_path, F_OK))
			execve(try_path, cmd, NULL);
		free(try_path);
		i++;
	}
	free_str(cmd);
}

