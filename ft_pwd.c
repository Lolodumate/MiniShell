#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);;
		return (TRUE);
	}
	perror("ft_pwd");
	return (FALSE);
}
