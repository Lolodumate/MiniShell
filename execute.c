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

void	exec_command(t_cmd cmd, char *input)
{
//	if (cmd.type_cmd == BUILTIN)
//		run_builtin(cmd, cmd.lst);
	if (cmd.type_cmd == HEREDOC)
		run_heredoc(cmd.lst);
	else
		exec_single_command(cmd, input);
}

// Fonction d'execution d'une commande binaire simple
bool	exec_single_command(t_cmd cmd, char *input)
{
	char	*try_path;
	char	**command;
	
	command = ft_split(input, ' ');
	try_path = find_the_right_path(input, cmd.paths);
	if (execve(try_path, command, NULL) == -1)
	{
		free_str(try_path);
		exit_error("command not found");
		return (false);
	}
	free_str(try_path);
	free_double_str(command);
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
