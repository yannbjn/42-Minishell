/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:59:57 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/29 12:57:19 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_input(t_shell *shell, t_lex *lex, t_cmd *cmd, t_fds *fd)
{
	if (fd->input != -42 && fd->input != -1)
		close(fd->input);
	if (lex->token == LOWER)
	{
		fd->input = open(lex->next->word, O_RDONLY);
		if (fd->input == -1)
		{
			if (shell->inflagerr == 0)
				fd_printf(2, "minishell: %s: %s\n", lex->next->word, NOSUCH);
			shell->excode = 1;
			shell->inflagerr = 1;
		}
	}
	else if (lex->token == D_LOWER)
	{
		ft_sig_heredoc();
		if (!lex->quotelim)
			here_doc_exp(shell, cmd, lex, fd);
		else if (lex->quotelim)
			here_doc(shell, cmd, lex, fd);
		ft_signals();
	}
}

static void	handle_output(t_shell *shell, t_token tok, char *file, t_fds *fd)
{
	if (fd->output != -42 && fd->output != -1)
		close(fd->output);
	if (tok == GREATER)
		fd->output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd->output = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd->output == -1)
	{
		shell->excode = 1;
		if (shell->outflagerr == 0)
			ft_perror(shell, file, strerror(errno), NULL);
		shell->outflagerr = 1;
	}
}

void	handle_redir(t_shell *shell, t_cmd *cmd, t_fds *fd)
{
	t_lex	*curr;

	curr = cmd->redir;
	while (curr)
	{
		if (curr->token == LOWER || curr->token == D_LOWER)
			handle_input(shell, curr, cmd, fd);
		if (curr->token == D_GREATER || curr->token == GREATER)
			handle_output(shell, curr->token, curr->next->word, fd);
		curr = curr->next;
	}
}

void	prep_exec(t_shell *shell, t_fds *fd)
{
	t_cmd	*node;
	t_cmd	*cmd;

	fd->redir[0] = -42;
	node = shell->cmd;
	cmd = shell->cmd;
	while (cmd)
	{
		check_builtins(cmd);
		cmd = cmd->next;
	}
	shell->tabpath = get_execpath(shell);
	handle_withpath(shell, node, -1, 0);
}
