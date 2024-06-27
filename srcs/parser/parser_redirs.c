/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:34:26 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:36:15 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_redir(t_cmd *curr_cmd, t_lex *curlex, t_lex **head)
{
	t_lex	*latex;

	if (curlex->prev)
		curlex->prev->next = curlex->next;
	else
		*head = curlex->next;
	if (curlex->next)
		curlex->next->prev = curlex->prev;
	curlex->next = NULL;
	if (!curr_cmd->redir)
	{
		curr_cmd->redir = curlex;
		curlex->prev = NULL;
	}
	else
	{
		latex = curr_cmd->redir;
		while (latex->next)
			latex = latex->next;
		latex->next = curlex;
		curlex->prev = latex;
	}
}

t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		exitmsg(shell, MERROR);
	return (new_cmd);
}

t_cmd	*split_redir(t_shell *shell, t_lex **head)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;
	t_lex	*curlex;
	t_lex	*next_node;
	t_cmd	*new_cmd;

	cmd_list = init_cmd(shell);
	curr_cmd = cmd_list;
	curlex = *head;
	while (curlex != NULL)
	{
		next_node = curlex->next;
		if (curlex->token == PIPE)
		{
			new_cmd = init_cmd(shell);
			curr_cmd->next = new_cmd;
			new_cmd->prev = curr_cmd;
			curr_cmd = new_cmd;
		}
		else if (curlex->isred == true)
			redir_redir(curr_cmd, curlex, head);
		curlex = next_node;
	}
	return (cmd_list);
}
