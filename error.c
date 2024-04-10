/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:02:16 by laroges           #+#    #+#             */
/*   Updated: 2024/03/28 17:02:59 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_cmd cmd, const char *message, int exit_code)
{
	rl_clear_history();
	if (cmd.paths)
		free_double_str(cmd.paths);
	if (cmd.cmdin)
		free_double_str(cmd.cmdin);
	if (cmd.env)
		free_env(cmd.env);
	if (cmd.p.end)
		free_end(cmd.p.end, cmd.nb_pipe);
	perror(message);
	exit(exit_code);
}

void	clean_all(t_cmd cmd)
{
	rl_clear_history();
	if (cmd.paths)
		free_double_str(cmd.paths);
	if (cmd.cmdin)
		free_double_str(cmd.cmdin);
	if (cmd.env)
		free_env(cmd.env);
	if (cmd.p.end)
		free_end(cmd.p.end, cmd.nb_pipe);
}
