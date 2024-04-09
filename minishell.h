/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:56:06 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/04 15:49:29 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef READLINE_PROMPT
#  define READLINE_PROMPT "\033[92m minishell-1.42$ \033[0m"
# endif

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tok
{
	char			*str;
	int				type;
	struct s_tok	*next;
}					t_tok;

// L'inclusion de exec.h doit se faire apres la declaration de la structure t_tok pour me permettre d utiliser cette derniere.
# include "exec.h"

typedef struct s_list
{
	int				content;
	int				pos;
	struct s_list	*next;
}					t_list;

typedef struct s_var_expand
{
	char	*var_start;
	char	*var_value;
	char	*var_end;
	char	*new_str;
	int		ret_value;
}				t_var_expand;

enum				e_token
{
	DSUP,
	DINF,
	INF,
	SUP,
	PIPE,
	WORD
};


//	ancien parsing cas par cas
int					syntax_first_pipe(char *input);
int					syntax_last_input(char *input);
int					syntax(char *input);
int					chevron(char *input);
int					chevron_space(char *input);
void				print_no_quotes(char *input);
void				ignore_quotes(char *input, int *i);

//	initalisation de l env
t_env				*grab_env(char **str);
char				*ret_env_value(t_env *env, t_tok *lst);

//	utils tokenisation

void				print_tab_tok(t_tok *tok);
t_tok				*ft_lstnew_tok(char *str, int type);
void				ft_lstadd_back_tok(t_tok **lst, t_tok *new);
t_tok				*is_token(char *input);
int					ft_separator(char c);
int					count_len_tok(char *input);
char				*tok_quote(char *input);

//	utils expand
char				*find_next_var(char *str);
void				extract_var_name(char *var_start, char *var_name);
char				*find_var_value(t_env *env, char *var_name);
char				*construct_new_str(char *old_str, char *var_start,
						char *var_end, char *var_value);

//	parsing automate
bool				check(t_tok *token);
bool				etat_init(t_tok *token);
bool				etat_1(t_tok *token);
bool				etat_2(t_tok *token);
bool				etat_3(t_tok *token);
char				*ret_no_quotes(char *input, int *i);

//	parsing quotes
int					parsing(char *input);
int					check_quotes(char *input);

void				expand(t_env *env, t_tok *lst);

// free.c
void				free_str(char *str);
void				free_double_str(char **str);
void				free_list(t_tok *lst);
void				free_end(int **end, int n);

// error.c
void				exit_error(const char *error);

// ************ libft functions **************************

char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(char	*s1, char *s2);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

#endif
