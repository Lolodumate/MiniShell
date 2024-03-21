#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (TRUE);
	return (FALSE);
}

void	exec_builtin(char **args/*, t_env *env*/)
{
/*	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, env->env);
*/	if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
/*	if (ft_strcmp(args[0], "env") == 0)
		ft_env(env->env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, env->env);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, env);
*/
}
