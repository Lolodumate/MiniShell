/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:04:58 by laroges           #+#    #+#             */
/*   Updated: 2024/03/08 16:52:02 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metacharacter(char *c)
{
	if (c == "<")
	       return (LESS);
	if (c == "<<")
	       return (LESSLESS);
	if (c == ">")
		return (GREAT);
	if (c == ">>")
	       return (GREATGREAT);
	if (c == "|")
	       return (PIPE);
	if (c == "$")
		return (DOLLAR);
	if (c == "&")
		return (AMPERSAND);
	if (c == ".")
		return (NOTOKEN);
	return (FALSE);
}
