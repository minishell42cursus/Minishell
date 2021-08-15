NAME		=	minishell

SRCS_FILES	= 	minishell.c \
				inicialise.c \
				raise_error.c \
				builtins/ft_pwd.c \
				builtins/ft_echo.c \
				signals/signal.c \
				execute/run_command.c \

MAIN_DIR	=	srcs/

SRCS		= 	$(addprefix $(MAIN_DIR),$(SRCS_FILES))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I ./includes/ -I ./libft/ -I ~/.brew/opt/readline/include

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

LIB			= ./libft/libft.a

RDL			= -lreadline

RDL_MAC		= -lreadline -L ~/.brew/opt/readline/lib



all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)

$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS) $(LIB) $(RDL_MAC)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

-include	$(OBJS:.o=.d)
