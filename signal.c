/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:16 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 15:48:54 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(char *input, t_var_expand *shell)
{
	if (g_signum == SIGINT)
	{
		shell->ret_value = 130;
		g_signum = 0;
	}
	if (g_signum == SIGQUIT)
	{
		shell->ret_value = 131;
		g_signum = 0;
	}
	if (!input)
		exit_and_free(input, shell, shell->ret_value);
}
