NAME		=	minishell
LIBFT		=	libft.a

# Source directories:

MAIN_DIR	=	srcs/
SIG_DIR		=	signals/
ERR_DIR		=	error/
PARSE_DIR	=	parser/
EXEC_DIR	=	execute/
BLTIN_DIR	=	builtins/
LIBFT_DIR	=	libft/

# Source files:

SRCS_FILES	= 	minishell \
				initialize \
				raise_error

SRC_BLTIN	= 	ft_pwd \
				ft_echo

SRC_PARSE	=	comma_parser \
				forbidden_stuff_parser \
				initial_parser

SRC_SIG		= 	signal

SRC_EXEC	=	run_command

SRC_ERR		=	stderr_outputs

SRCS		= 	$(addsuffix .c, $(addprefix $(MAIN_DIR),$(SRCS_FILES))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(SIG_DIR),$(SRC_SIG)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(ERR_DIR),$(SRC_ERR)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(PARSE_DIR),$(SRC_PARSE)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(EXEC_DIR),$(SRC_EXEC)))) \
				$(addsuffix .c, $(addprefix $(MAIN_DIR),$(addprefix $(BLTIN_DIR),$(SRC_BLTIN))))

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I ./includes/ -I ./libft/ -I ~/.brew/opt/readline/include

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

RDL			= -lreadline

RDL_MAC		= -lreadline -L ~/.brew/opt/readline/lib

LIBFT_MAC	= -L libft/ -lft

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)

$(NAME):	$(OBJS) $(LIBFT_DIR)$(LIBFT) 
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS) $(RDL_MAC) $(LIBFT_MAC)

$(LIBFT_DIR)$(LIBFT):	$(LIBFT_DIR)
			@make -C $(dir $(LIBFT_DIR))

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			@make -C $(dir $(LIBFT_DIR)) clean

fclean:		clean
			@make -C $(dir $(LIBFT_DIR)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

-include	$(OBJS:.o=.d)
