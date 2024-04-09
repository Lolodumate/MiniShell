#include "minishell.h"
#include "exec.h"

// Fonction de determine si une commande est un heredoc
bool	is_heredoc(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (is_dinf_token(cmd, i))
		{
			i += 2;
			if (!cmd[i])
			{
				printf("is_heredoc : !cmd[i]\n");
				return (false);
			}
			while (cmd[i])
			{
				if (!is_metacharacter(cmd, i))
					return (true);
				i++;
			}
			if (!cmd[i])
				return (false);
			return (true);
		}	
		i++;
	}
	return (false);
}

// Boucle heredoc
void	run_heredoc(t_tok *lst)
{
//	int		end[2];
	char	*buff;
	char	*delimiter;

//	if (pipe(end) == -1)
//		exit_error("pipe");
	delimiter = get_delimiter(lst);
	while (1)
	{
		buff = readline("> ");
		if (!ft_strncmp(buff, delimiter, ft_strlen(delimiter)))
		{
			free(delimiter);
			break ;
		}
//		ft_putendl_fd(buff, end[1]);
	}
/*	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
*/
	free(buff);
/*	if (lst->type == DINF)
		close(STDOUT_FILENO);
*/
}
