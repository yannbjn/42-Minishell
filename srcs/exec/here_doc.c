/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:13:49 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 15:15:06 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ctrlc(t_shell *shell, t_fds *fd, t_cmd *cmd)
{
	if (g_sig == SIGINT)
	{
		shell->excode = 130;
		g_sig = 0;
		close(fd->input);
		dup2(fd->in, STDIN_FILENO);
		unlink(cmd->heredoc);
		shell->tmpexcode = 130;
	}
}

void	hd_file(t_shell *shell, t_cmd *cmd)
{
	while (access(cmd->heredoc, F_OK) == 0)
		cmd->heredoc = ft_strjoinfree(cmd->heredoc, "a");
	if (!cmd->heredoc)
		exitmsg(shell, MERROR);
}

int	here_doc(t_shell *shell, t_cmd *cmd, t_lex *lex, t_fds *fd)
{
	int		tmp;
	char	*str;

	cmd->heredoc = ft_strdup("/tmp/.here_doc_a");
	if (!cmd->heredoc)
		exitmsg(shell, MERROR);
	hd_file(shell, cmd);
	tmp = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd->input = open(cmd->heredoc, O_RDONLY);
	fd->in = dup(STDIN_FILENO);
	str = readline("> ");
	while (str && !ft_strictcmp(lex->next->word, str))
	{
		write(tmp, str, ft_strlen(str));
		write(tmp, "\n", 1);
		free(str);
		str = readline("> ");
	}
	ctrlc(shell, fd, cmd);
	return (close(tmp), free(str), free(cmd->heredoc), close(fd->in), 130);
}
