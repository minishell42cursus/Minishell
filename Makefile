NAME		=	minishell

SRCS_FILES	= 	builtins/ft_pwd.c \

MAIN_DIR	=	srcs/

SRCS		= 	$(addprefix $(MAIN_DIR),$(SRCS_FILES))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include -I./libs/libft/ -I ~/.brew/opt/readline/include

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
