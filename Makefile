SRCS = 	code.c \
		quotes.c\
		syntaxe.c\
		parsing.c\
		utils.c\
		expand.c\
		token.c\
		utils_token.c\
		path.c\
		libft/ft_calloc.c\
		libft/ft_memset.c\
		libft/ft_split.c\
		libft/ft_strjoin.c\
		libft/ft_strlcpy.c\
		libft/ft_strncmp.c\
		libft/ft_substr.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		execute.c \
		free.c \


SRCS_DIR = src/
OBJS_DIR = obj/

OBJS = $(SRCS:.c=.o)

NAME = Minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -I.
RM = rm -f

all: $(NAME)

##############   barre de chargement    ##############

	@echo -n "\033[35m [EXECUTION] \033[0m: Compiling Minishell... "
	@total_iterations=40; \
	i=0; \
	while [ $$i -lt $$total_iterations ]; do \
		sleep 0.01; \
		printf "\033[35m▇\033[0m"; \
		i=$$((i + 1)); \
	done
#header nom du programme

	@echo
	@echo
	@echo "\033[32m =========== Compilation completed successfully.=========== \033[0m"
	@echo 
	@echo "\033[36m  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \033[0m"     
	@echo "\033[36m  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      \033[0m"
	@echo "\033[36m  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       \033[0m"   
	@echo "\033[36m  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        \033[0m"  
	@echo "\033[36m  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗    \033[0m" 
	@echo "\033[34m  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝	 \033[0m"

	@echo
	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline -lhistory


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) $(OBJS)

#header du clean
	@echo
	@echo "\033[35;5m =========== OBJ was removed.=========== \033[0m"
	@echo
	@echo "\033[35m ██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗ \033[0m"
	@echo "\033[35m ██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗ \033[0m"
	@echo "\033[35m ██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██║  ██║ \033[0m"
	@echo "\033[35m ██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██║  ██║ \033[0m"
	@echo "\033[35m ██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██████╔╝ \033[0m"
	@echo "\033[35m ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═════╝  \033[0m"
	@echo

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

#header du fclean
	@echo
	@echo "\033[31;5m =========== All was removed.=========== \033[0m"
	@echo
	@echo "\033[31m ██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗ \033[0m"
	@echo "\033[31m ██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗ \033[0m"
	@echo "\033[31m ██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██║  ██║ \033[0m"
	@echo "\033[31m ██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██║  ██║ \033[0m"
	@echo "\033[31m ██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██████╔╝ \033[0m"
	@echo "\033[31m ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═════╝  \033[0m"
	@echo

re: fclean all

.PHONY: clean fclean all re                                   
