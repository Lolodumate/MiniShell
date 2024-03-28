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

// execute.c
void				exec_command(char *input, char **paths);
char				*find_the_right_path(char *input, char **paths);

// process.c
void	child_process(char *cmd, int *end, char **envp);
void	parent_process(char *cmd, int *end, char **envp);

// pipe.c
bool	is_pipe(char c);
int	nb_pipe(char *input);
int	*init_pipe(int end[2]);
void	exec_pipe(char *input, char **envp);

// path.c
int					find_path(char **envp, char *to_find);
char				*add_backslash(char *path);
char				**check_backslash(char **paths);
char				**get_paths(char **envp);

#endif
