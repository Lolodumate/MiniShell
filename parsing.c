/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:45:29 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/26 10:18:22 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	etat_0(t_tok *token)
{
	if (!token)
		return (true);
	if (token->type == WORD)
		return (etat_1(token->next));
	else if (token->type == DSUP || token->type == DINF || token->type == INF
		|| token->type == SUP)
		return (etat_2(token->next));
	else
		return (false);
}

bool	etat_1(t_tok *token)
{
	if (!token)
		return (true);
	if (token->type == WORD)
		return (etat_1(token->next));
	else if (token->type == DSUP || token->type == DINF || token->type == INF
		|| token->type == SUP)
		return (etat_2(token->next));
	else if (token->type == PIPE)
		return (etat_3(token->next));
	else
		return (false);
}

bool	etat_2(t_tok *token)
{
	if (!token)
		return (false);
	if (token->type == WORD)
		return (etat_1(token->next));
	else if (token->type == DSUP || token->type == DINF || token->type == INF
		|| token->type == SUP)
		return (false);
	else
		return (false);
}

bool	etat_3(t_tok *token)
{
	if (!token)
		return (false);
	if (token->type == WORD)
		return (etat_1(token->next));
	else if (token->type == DSUP || token->type == DINF || token->type == INF
		|| token->type == SUP)
		return (etat_2(token->next));
	else
		return (false);
}

bool	check(t_tok *token)
{
	if (etat_0(token) == false)
		return (write(2, "\033[91m >> Minishell: Syntaxe error\n", 35), false);
	return (etat_0(token));
}
