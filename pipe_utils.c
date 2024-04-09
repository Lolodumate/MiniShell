#include "minishell.h"
#include "exec.h"

t_pipe	init_pipe_data(int nb_pipe)
{
	t_pipe	p;

	p.i = -1;
	p.nb_pipe = nb_pipe;
	p.redir = false;
	p.end = NULL;
	if (nb_pipe > 0)
		p.end = set_pipe(p, nb_pipe);
	p.cmd = NULL;
	return (p);
}

// Comptage du nombre de pipes entres dans la chaine de caracteres input
int	nb_pipe(char *input)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (input[++i])
	{
		if (input[i] == '|')
			n++;
	}
	return (n);
}

// Si le token est un '|' alors on ouvre un pipe avec cette fonction
int	init_pipe(int **end, int i)
{
	if (pipe(end[i]) == -1)
	{
		// Ajouter fonction de liberation de la memoire avant de quitter
		exit_error("pipe");
	}
	return (EXIT_SUCCESS);
}

int	**set_pipe(t_pipe p, int nb_pipe)
{
	p.end = (int **)malloc(sizeof(int *) * nb_pipe);
	if (!p.end)
	{
		perror("malloc pipe");
		return (NULL);
	}
	while ((++p.i < nb_pipe) && nb_pipe > 0)
	{
		p.end[p.i] = (int *)malloc(sizeof(int) * 2);
		if (!p.end[p.i])
		{
			free_end(p.end, nb_pipe);
			perror("malloc pipe");
			return (false);
		}
		p.end[p.i][0] = 0;
		p.end[p.i][1] = 0;
	}
	return (p.end);
}
