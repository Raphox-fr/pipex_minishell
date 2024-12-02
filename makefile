### WELCOME TO HELL ###


### COLOR ###
RED = \e[31m
MAJA = \e[35m
GREEN = \e[32m
END = \e[0m


### NAME ###
NAME = minishell

### INC ###
DIRINC = ./includes/

### LIB ###
DIRLIBFT = ./lib/libft

### SRC ###
SRCDIR = src/
SRC =		main.c \
			error.c \
			utils.c \
			execute.c \
			builtins/builtins.c \
			pipex_bonus/pipex_bonus.c \
			pipex_bonus/my_split.c \
			pipex_bonus/tools.c \
			pipex_bonus/check_redirections.c \
			pipex_bonus/tools_built.c \
			pipex_bonus/build_command.c \
			builtins/error.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			Parse/count.c \
			Parse/checker_syntax.c \
            Parse/checker_syntax_tool.c \
			Parse/find_name_later.c \
			Parse/fill_parsing_tree.c \
			Parse/fill_parsing_tree_1.c \
			Parse/Parsing.c \
			Parse/Parsing_tool.c \
			Parse/parsing_tree.c \
			Parse/Parsing_tree_tool_1.c \
			Parse/parsing_tree_tool.c \
			Parse/quote.c \
			Parse/set_value.c \
			Parse/variable.c \
			Parse/free.c \
			# builtins/tools.c \

SRCS = $(addprefix $(SRCDIR), $(SRC))

### OBJ ###
OBJDIR = obj/
PARS_OBJDIR = $(OBJDIR)/Parse
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

### COMPILE ###
CC = cc
CCFLAG = -Wextra -Wall -g3
INCFLAG = -I$(DIRINC)
LIBFTDIR = ./lib/libft/
PIPEXDIR = pipex/

all:$(NAME)
	@echo "$(tput bold)$(GREEN)$@ is compile$(END)";

libft:
	@if [ ! -f "libft.a" ]; then \
		make -s -C $(LIBFTDIR) all ;\
		cp $(LIBFTDIR)libft.a ./; \
	fi;

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAG) $(INCFLAG) -c $< -o $@
	@echo "$(tput dim) $(MAJA)$<$(END)"

$(NAME): libft $(OBJS)
	@$(CC) $(CCFLAG) $(INCFLAG) $(OBJS) libft.a -lreadline -o $@

val: all
	valgrind ./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm libft.a
	@echo "$(RED)objet of $(NAME) is removed$(END)"

fclean: clean
	@rm $(NAME)
	@make -C $(LIBFTDIR) clean
	@echo "$(RED)objet and exec of $(NAME) is removed$(END)"

re: fclean all
	@make -C $(LIBFTDIR) fclean
	@echo $(NAME) is recompiled
