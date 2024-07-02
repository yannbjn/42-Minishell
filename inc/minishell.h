/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:35:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/07/02 13:21:02 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERRARG "No args allowed"
# define MERROR "Malloc error"
# define SYNTERR "syntax error near unexpected token"
# define NOSUCH "No such file or directory"
# define CMDFAIL "command not found"
# define NOTV "not a valid identifier"
# define E "export"

extern int			g_sig;

typedef enum e_token
{
	NOT_TOKEN,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_token;

typedef enum e_builtin
{
	NOT,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}					t_builtin;

typedef struct s_lex
{
	char			*word;
	bool			istoken;
	bool			isred;
	bool			quotelim;
	int				i;
	t_token			token;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	bool			isunset;
	bool			oldpwd;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_path
{
	char			*pwd;
	char			*oldpwd;
}					t_path;

typedef struct s_fds
{
	int				pipes[2];
	int				redir[2];
	int				input;
	int				output;
	int				in;
	int				savedpipe;
	bool			prevpipe;

}					t_fds;

typedef struct s_cmd
{
	char			**tab;
	char			*path;
	bool			pathnoaccess;
	t_builtin		builtin;
	int				num_redirections;
	t_fds			*fds;
	char			*heredoc;
	t_lex			*redir;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_flags
{
	bool			entrecote;
	bool			quoterotie;
	bool			flag;
	bool			entrentrecote;
	int				i;
}					t_flags;

typedef struct s_export
{
	char			*value;
	char			*key;
	int				i;
	int				j;
	int				flag;
	int				h;
}					t_export;

typedef struct s_shell
{
	char			*cwd;
	char			**envp;
	char			**tabpath;
	t_path			*path;
	t_env			*env;
	t_lex			*lex;
	t_cmd			*cmd;
	int				excode;
	int				tmpexcode;
	char			*inp;
	char			*newinp;
	char			*finalinp;
	int				inflagerr;
	int				outflagerr;
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				ft_getenv(t_shell *shell, char **envp);
void				ft_no_env(t_shell *shell);

void				exitmsg(t_shell *shell, char *errmsg);
void				ft_perror(t_shell *shell, char *word, char *msg,
						char *third);
void				ft_freeshell(t_shell *shell);
void				resetloop(t_shell *shell);
void				freelex(t_lex **lex);
void				freecmd(t_cmd **cmd);
void				resetshell(t_shell *shell);
void				freeenv(t_env **env);
void				ft_freeshell(t_shell *shell);
void				initinitinit(t_shell *shell);
char				*ft_strdupfree(char *s);

void				expander(t_shell *shell);
void				handle_d_lower(char *tmp, t_flags *flags);
void				handle_quotes(char c, t_flags *flags);
char				*expand_dollar(t_shell *shell, char *str, t_flags *flags,
						t_env *node);
char				*is_not_alnum(t_shell *shell, char *str, int j);
char				*is_num(char *str, int j);
char				*ftsjb(char *s1, char *s2);
char				*ft_strdupfree(char *s);
char				*pos_no_quotes(char *wrd);
char				*pos_quotes(char *str);

void				lexer(t_shell *shell, char *input);
void				renegentrecote(t_shell *shell, int i);

void				tokenizer(t_shell *shell);
void				fill_lex_nodes(t_shell *shell, t_lex *new, int *i, int *j);
void				assign_enum(t_lex *new);
void				is_redir(t_shell *shell);
void				check_syntax(t_shell *shell, t_lex *new, int f);

void				parser(t_shell *shell);
t_cmd				*split_redir(t_shell *shell, t_lex **head);
t_cmd				*init_cmd(t_shell *shell);
void				notrimherelim(t_shell *shell);
void				split_cmd(t_shell *shell);
size_t				count_char(char *str);
int					checkifquotes(char *str);
void				backtoascii(t_shell *shell);

// prep exec path
void				launch_exec(t_shell *shell);
void				start_exec(t_shell *shell, t_cmd *cmd);
void				prep_exec(t_shell *shell, t_fds *fd);
void				handle_redir(t_shell *shell, t_cmd *cmd, t_fds *fd);
void				handle_withpath(t_shell *shell, t_cmd *c, int i, int flag);
int					withpath(t_shell *shell, t_cmd **c);
char				**get_execpath(t_shell *shell);
void				close_fds(t_fds *fd);
void				close_fds_parent(t_fds *fd);
void				set_redirs(t_fds *fd);
void				init_fds(t_fds *fd);
void				ft_pipes(t_shell *shell, t_cmd *cmd, t_fds *fd);
void				check_builtins(t_cmd *cmd);
void				child_builtin(t_shell *shell, t_cmd *cmd, t_fds *fd);
void				exec_builtin(t_shell *shell, t_cmd *cmd);
int					here_doc_exp(t_shell *shell, t_cmd *cmd, t_lex *lex,
						t_fds *fd);
int					here_doc(t_shell *shell, t_cmd *cmd, t_lex *lex, t_fds *fd);
void				ctrlc(t_shell *shell, t_fds *fd, t_cmd *cmd);
void				hd_file(t_shell *shell, t_cmd *cmd);

void				fill_envp(t_shell *shell);
void				add_toenv(t_shell *shell, t_export *exp);
void				update_envp(t_shell *shell);

// builtins
void				ft_exit(t_shell *shell, t_cmd *cmd, t_fds *fd);
void				ft_echo(t_shell *shell, t_cmd *cmd);
void				ft_cd(t_shell *shell, t_cmd *cmd);
void				ft_pwd(t_shell *shell, t_cmd *cmd);
void				ft_export(t_shell *shell, t_cmd *cmd);
void				ft_unset(t_shell *shell, t_cmd *cmd);
void				ft_env(t_shell *shell, t_cmd *cmd);

void				ft_signals(void);
void				ft_sig_heredoc(void);
void				sig_heredoc(int s);
void				handle_sig(int s);
bool				catchsignals(t_shell *shell);

#endif