#include "minishell.h"
#include "exec.h"

// Fonction qui retourne le delimiteur
char	*get_delimiter(t_tok *lst)
{
	char	*delimiter;
	t_tok	*tmp;

	delimiter = NULL;
	tmp = NULL;
	while (lst)
	{
		if (!lst->next)
			return (NULL);
		tmp = lst->next;
		if (lst->type == DINF)
		{
			if (tmp->type == WORD)
			{
				delimiter = ft_strdup(tmp->str);
				break ;
			}
			else
				return (NULL);
		}
		lst = tmp;
	}
	return (delimiter);
}

/*
bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
*/
/*
Metacharacters are: pipe (|), ampersand (&), semicolon (;), less-than sign (<), greater-than sign (>), left parenthesis ((), right parenthesis ()), dollar sign ($), backquote (`), backslash (\), right quote ('), double quotation marks ("), newline character, space character, and tab character.*/

bool	is_metacharacter(char *str, int i)
{
	if (!str[i])
		return (false);
	if (str[i] == '|' || str[i] == '&')
		return (true);
	if (str[i] == '<' || str[i] == '>')
		return (true);
	if (str[i] == '(' || str[i] == ')')
		return (true);
	if (str[i] == '$' || str[i] == '\'')
		return (true);
	if (str[i] == '\\' || str[i] == '`')
		return (true);
	if (str[i] == '\n' || str[i] == '"')
		return (true);
	if (str[i] == ' ' || str[i] == '\t')
		return (true);
	return (false);
}

bool	is_inf(char c)
{
	if (c == '<')
		return (true);
	return (false);
}

bool	is_dinf_token(char *str, int i)
{
	if (!str[i])
		return (false);
	if (is_inf(str[i]))
	{
		i++;
		if (!str[i])
			return (false);
		if (is_inf(str[i]))
		{
			i++;
			if (!str[i] || (str[i] && !is_inf(str[i])))
				return (true);
		}
	}
	return (false);
}

// Version char ** (cas ou le double chevron  et le delimiteur sont separes)
/*
char	*get_delimiter(char **input)
{
	int		i;
	int		j;
	char	*delimiter;

	i = 0;
	j = 0;
	delimiter = NULL;
	while (input[j])
	{
		while (input[j][i])
		{
			if (is_dinf_token(input[j], i))
			{
				j++;	
				ft_strlcpy(delimiter, input[j], ft_strlen(input[j]));
				return (delimiter);
			}
			i++;
		}
		j++;
	}
	return (delimiter);
}
*/

// Mini tokenisation de la commande heredoc
char	**get_tokens_heredoc_cmd(char *cmd)
{
	int		i;
	int		j;
	char		**ret;

	i = 0;
	j = -1;
	ret = ft_split(cmd, '<');
	while (ret[++j])
	{
		printf("[%d]", j);
		while (ret[j][i])
		{
			printf("%c", ret[j][i]);
			i++;
		}
		i = 0;
		printf("\n");
	}
	return (ret);
}
