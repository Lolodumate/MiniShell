#include "minishell.h"
#include "exec.h"

void	handle_dup2(t_cmd cmd, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		clean_exit(cmd, "dup2", EXIT_FAILURE);
}

t_cmd	init_cmd(t_cmd cmd, t_tok *lst, t_env *env, char **envp)
{
	cmd = (t_cmd){0};
	cmd.paths = get_paths(envp);
	cmd.type_cmd = -1;
	cmd.lst = lst;
	cmd.env = env;
	return (cmd);
}

t_cmd	set_cmd(t_cmd cmd, char *input)
{
	cmd.cmdin = get_cmd(input);
	cmd.nb_pipe = nb_pipe(input);
	cmd.p = init_pipe_data(cmd.nb_pipe);
	cmd.type_cmd = get_type_command(cmd, input);
	return (cmd);
}

char	**get_cmd(char *input)
{
	char	**cmd;
	cmd = ft_split(input, '|');
	return (cmd);
}

// Fonction qui retourne un indicateur qui permet d'orienter l'execution de la commande
int	get_type_command(t_cmd cmd, char *input)
{
/*      if (!is_builtin(input))
                type = BIN;
        if (is_builtin(input))
                type = BUILTIN;
        if (is_redir(input))
                type = REDIR;
*/
	if (is_heredoc(input))
		cmd.type_cmd = HEREDOC;
	return (cmd.type_cmd);
}

