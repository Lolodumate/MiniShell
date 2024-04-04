/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:56:06 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 17:08:36 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# ifndef READLINE_PROMPT
#  define READLINE_PROMPT "\033[92m minishell-1.42$ \033[0m"
# endif

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

typedef struct	s_pipe
{
	int		i;
	int		nb_pipe;
	int		**end;
	char	*cmd;
}		t_pipe;

// execute.c
char				**get_cmd(char *input);
bool				exec_command(char *input, char **paths);
char				*find_the_right_path(char *input, char **paths);

// utils_exec.c
bool	redir(char *cmd); // Fonction qui determine si une commande contient une redirection

// process.c
int	close_pipe(int **end, int i, int j);
bool	child_process(t_pipe p, char *cmd, char **envp, int *fd);
void	parent_process(t_pipe p, int *fd);
void	last_child_process(char *cmd, char **envp, int fd);
void	last_parent_process(int fd);

// pipe.c
t_pipe	init_pipe_data(void);
int	nb_pipe(char *input);
int	init_pipe(int **end, int i);
void	exec_no_pipe_command(char *cmd, char **envp);
void	exec_pipe(char **input, char **envp, int nb_pipe);

// path.c
int					find_path(char **envp, char *to_find);
char				*add_backslash(char *path);
char				**check_backslash(char **paths);
char				**get_paths(char **envp);

#endif
