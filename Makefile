NAME		=	minishell

CC			=	cc

FLAG		=	-g3 -Wall -Wextra -Werror
#FLAG		=	-g3

LDFLAGS		=	-lreadline

LIBFT_PATH	=	libft

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE		=	srcs/main.c \
				srcs/inits/inits.c \
				srcs/inits/get_env.c srcs/inits/ft_no_env.c \
				srcs/resetfreexit/exitmsg.c srcs/resetfreexit/resetloop.c \
				srcs/lexer/lexer.c srcs/lexer/lexer_utils.c \
				srcs/lexer/expand.c srcs/lexer/expand_utils.c \
				srcs/lexer/expand2.c srcs/lexer/tokenizer.c \
				srcs/parser/parser.c  srcs/parser/parser2.c \
				srcs/parser/parser_utils.c srcs/parser/parser_redirs.c \
				srcs/parser/parse_handle_heredoclim.c \
				srcs/exec/exec.c srcs/exec/path.c srcs/builtins/exit.c \
				srcs/exec/prep_exec.c srcs/exec/redirs_fds.c srcs/exec/handle_builtins.c \
				srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/pwd.c \
				srcs/builtins/export.c srcs/builtins/exportbis.c \
				srcs/builtins/unset.c srcs/builtins/env.c \
				srcs/exec/here_doc.c srcs/exec/here_doc_exp.c \
				srcs/signals/signals.c \

OBJS		=	$(C_FILE:.c=.o)

BOBJS		=	$(BC_FILE:.c=.o)

.c.o:
			$(CC) $(FLAG) -c $< -o $@

all:		$(NAME)

ball:		$(NAME) $(BNAME)

$(LIBFT_LIB):
			make -C $(LIBFT_PATH)

$(NAME):	$(LIBFT_LIB) $(OBJS)
			$(CC) $(OBJS) $(LDFLAGS) $(LIBFT_LIB) -o $(NAME)

clean:		
			make clean -C $(LIBFT_PATH)
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)
			make fclean -C $(LIBFT_PATH)

re:			fclean all


.PHONY:		all clean fclean re
