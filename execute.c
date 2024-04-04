/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:36 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 17:06:58 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

char	**get_cmd(char *input)
{
	char	**cmd;
	cmd = ft_split(input, '|');
	return (cmd);
}

bool	exec_command(char *input, char **paths)
{
	char	*try_path;
	char	**cmd;
	
	cmd = ft_split(input, ' ');
	try_path = find_the_right_path(input, paths);
	if (execve(try_path, cmd, NULL) == -1)
	{
		free_str(try_path);
	//	exit_error("command not found");
		return (false);
	}
	free_str(try_path);
	free_double_str(cmd);
	return (true);
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
