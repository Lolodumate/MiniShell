/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:42:32 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 15:43:02 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signum = SIGINT;
	}
}

void	sigint_handler2(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_signum = SIGINT;
	}
}

void	sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		close(STDIN_FILENO);
	}
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_signum = SIGQUIT;
	}
}

void	sigquit_handler2(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "", 1);
		g_signum = SIGQUIT;
	}
}