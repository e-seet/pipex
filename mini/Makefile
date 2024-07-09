# **************************************************************************** #
# Vars
# **************************************************************************** #
NAME        = minishell

# **************************************************************************** #
# Comp and flags
# **************************************************************************** #
CC := clang
# CFLAGS := -Wall -Wextra -Werror
CFLAGS := -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

# **************************************************************************** #
# Source
# **************************************************************************** #
SRC_FILES			:=	main.c	\
						./utils/generic/setup.c\
						./utils/generic/utils.c\
						./utils/lexical/lexical.c	\
						./utils/lexical/lexicalprocessing.c	\
						./utils/lexical/lexicalutils1.c	./utils/lexical/lexicalutils2.c	./utils/lexical/lexicalutils3.c \
						./utils/parsing/parsing.c\
						./utils/parsing/parsingutils.c\
						./utils/parsing/parsing1.c\
						./utils/parsing/parsing2.c\
						./utils/parsing/parsing3.c\
						./utils/parsing/parsing4.c\
						./utils/execute/execute.c\
						./utils/execute/executejob.c\
						./utils/execute/executesimplecommand.c\
						./utils/execute/executepipe.c\
						./utils/execution/execution_redir.c\
						./utils/execution/execution.c\
						./utils/execution/executionprep.c\
						./utils/signal.c\
						./utils/builtin/executionbuiltin.c\
						./utils/builtin/executioncd.c\
						./utils/builtin/setenv.c\
						./utils/builtin/unsetenv.c

OBJS				=	$(SRC_FILES:.c=.o)

# **************************************************************************** #
# Libft
# **************************************************************************** #
SRC_FILESLIBFT		:=	ft_isalpha.c		ft_isdigit.c		ft_isalnum.c		ft_isascii.c		ft_isprint.c		\
						ft_strlen.c				ft_memset.c			ft_bzero.c			ft_memcpy.c			ft_memmove.c		\
						ft_strlcpy.c			ft_strlcat.c		ft_tolower.c		ft_toupper.c		ft_strchr.c			\
						ft_strrchr.c			ft_strncmp.c 		ft_memchr.c			ft_memcmp.c			ft_strnstr.c		\
						ft_atoi.c				ft_calloc.c			ft_strdup.c			ft_substr.c			ft_strjoin.c		\
						ft_strtrim.c			ft_split.c			ft_itoa.c			ft_strmapi.c		ft_striteri.c		\
						ft_putchar_fd.c			ft_putstr_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c

LIBFT_DIR			=	../libft/
LIBFTSRC			=	$(addprefix $(LIBFT_DIR), $(SRC_FILESLIBFT))
OBJ_LIBFT			=	$(LIBFTSRC:.c=.o)

# **************************************************************************** #
# Get_Next_Line
# **************************************************************************** #
SRC_FILES_GNL		:=	get_next_line.c		get_next_line_utils.c
GNL_DIR				=	../get_next_line/
GNLSRC				=	$(addprefix $(GNL_DIR), $(SRC_FILES_GNL))
OBJ_GNL				=	$(GNLSRC:.c=.o)

# **************************************************************************** #
# Rules
# **************************************************************************** #
.PHONY: all bonus clean fclean re

$(NAME):	$(OBJ_LIBFT) $(OBJ_GNL)	$(OBJS)
#			@$(CC) $(OBJ_LIBFT) $(OBJ_GNL) $(OBJS) -o $(NAME)
			@$(CC) $(OBJ_LIBFT) $(OBJ_GNL) $(OBJS) -o $(NAME)  -L/opt/homebrew/opt/readline/lib  -I/opt/homebrew/opt/readline/include -lreadline

all: fclean $(NAME)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@ 

# Libft file compilation
$(OBJ_LIBFT): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_GNL): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm	-f	$(OBJS)
	rm	-f	$(OBJ_LIBFT)
	rm	-f	$(OBJ_GNL)

fclean: clean
	rm -f $(NAME)

re:	fclean
