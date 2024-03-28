/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:45:29 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 05:44:29 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	post-tokenisation etat initial commencement 
//uniquement par redirection ou word
bool	etat_init(t_tok *token)
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

//	etat du word et ses debouchees
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

//	etat des redirections et ses debouchees
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

//	etat des pipe et ses debouchees
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

// exec du parsing de l etat initial
bool	check(t_tok *token)
{
	if (etat_init(token) == false)
		return (write(2, "\033[91m >> Minishell: Syntaxe error\n", 35), false);
	return (etat_init(token));
}
