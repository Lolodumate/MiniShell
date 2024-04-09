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

# include "minishell.h"
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

typedef enum e_cmd_type
{
	BIN,
	BUILTIN,
	REDIR,
	HEREDOC

}	t_cmd_type;

typedef struct	s_pipe
{
	int			i;
	int			nb_pipe;
	int			**end;
	bool			redir;
	char		**cmd;
}	t_pipe;

typedef struct	s_cmd
{
	int			nb_pipe;
	char		**envp;
	char		**paths;
	char		**cmdin;
	t_pipe		p;
	t_cmd_type	type_cmd;
	t_tok		*lst;
}	t_cmd;

// execute_utils.c
t_cmd	init_cmd(t_cmd cmd, t_tok *lst, char **envp);
t_cmd	set_cmd(t_cmd cmd, char *input);
char	**get_cmd(char *input);
int				get_type_command(t_cmd cmd, char *input);

// execute.c
void	exec_command(t_cmd cmd, char *input);
bool	exec_single_command(t_cmd cmd, char *input);
char	*find_the_right_path(char *input, char **paths);

// Pipe management ************************************************************

// process.c
void	close_pipe(int **end, int i, int j);
void	child_process(t_cmd cmd, char *input, int *fd);
void	parent_process(t_cmd cmd, int *fd);
void	last_child_process(t_cmd cmd, char *input, int fd);
void	last_parent_process(int fd);

// pipe_utils.c
t_pipe	init_pipe_data(int nb_pipe);
int				nb_pipe(char *input);
int				init_pipe(int **end, int i);
int				**set_pipe(t_pipe p, int nb_pipe);

// pipe.c
void	exec_input(t_cmd cmd, char *input);
void	exec_pipe(t_cmd cmd, char *input);

// path.c
int				find_path(char **envp, char *to_find);
char	*add_backslash(char *path);
char	**check_backslash(char **paths);
char	**get_paths(char **envp);

// Heredoc management ********************************************************

// redirections.c
bool	is_heredoc(char *cmd);
void	run_heredoc(t_tok *lst);
//void	run_heredoc(char **input);

// heredoc_utils.c
char	*get_delimiter(t_tok *lst);
bool	is_metacharacter(char *str, int i);
bool	is_inf(char c);
bool	is_dinf_token(char *str, int i);
//char	*get_delimiter(char **input);
char	**get_tokens_heredoc_cmd(char *cmd);

#endif
