NAME        =   minishell

CC          =   cc

LIBS        =   /inc

FLAG        =   -g3 -Wall -Wextra -Werror

LDFLAGS     =   -lreadline

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILES     =   srcs/main.c \
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
                srcs/signals/signals.c

OBJ_DIR     =   builds

OBJS        =   $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))

DEPS        =   $(OBJS:.o=.d)

all:        $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs/inits \
		$(OBJ_DIR)/srcs/resetfreexit \
		$(OBJ_DIR)/srcs/lexer \
		$(OBJ_DIR)/srcs/parser \
		$(OBJ_DIR)/srcs/exec \
		$(OBJ_DIR)/srcs/builtins \
		$(OBJ_DIR)/srcs/signals

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAG) -MMD -MP -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME):    $(LIBFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBFT_LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ_DIR) $(DEPS)

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re:         fclean all

-include $(DEPS)

.PHONY:     all clean fclean re
