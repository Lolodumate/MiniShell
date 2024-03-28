/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:56:06 by abdmessa          #+#    #+#             */
/*   Updated: 2024/03/28 17:05:57 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

enum				e_token
{
	DSUP,
	DINF,
	INF,
	SUP,
	PIPE,
	WORD
};

typedef struct s_list
{
	int				content;
	int				pos;
	struct s_list	*next;
}					t_list;
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
t_tok				is_token(char *input);

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

void				update_token_values(t_env *env, t_tok *lst);

// free.c
void				free_str(char *str);
void				free_double_str(char **str);
void				free_list(t_tok *lst);

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
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				*ft_memset(void *s, int c, size_t n);

#endif
