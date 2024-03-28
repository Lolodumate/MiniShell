SRCS = 	code.c \
		quotes.c\
		syntaxe.c\
		parsing.c\
		utils.c\
		expand.c\
		token.c\
		utils_token.c\
		execute.c \
		path.c \
		init.c \
		pipe.c \
		process.c \
		free.c \
		ft_split.c \
		ft_strjoin.c \
		ft_substr.c \
		ft_strncmp.c  \
		ft_calloc.c \
		ft_strlcpy.c \
		ft_memset.c \

##############   Directories creation  ##############

SRCS_DIR = src/
OBJS_DIR = obj/


OBJS = $(SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
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
