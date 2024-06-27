/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resetloop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:46:32 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:03:38 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//we used to reset tmpexcode at 0 in this function
void	initinitinit(t_shell *shell)
{
	shell->tabpath = NULL;
	shell->inp = NULL;
	shell->newinp = NULL;
	shell->finalinp = NULL;
}

void	freelex(t_lex **lex)
{
	t_lex	*tmp;

	if (!lex)
		return ;
	while (*lex)
	{
		if ((*lex)->word)
			free((*lex)->word);
		tmp = (*lex)->next;
		free(*lex);
		*lex = tmp;
	}
}

void	freecmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_lex	*cmdlex;

	if (!cmd)
		return ;
	while (*cmd)
	{
		cmdlex = (*cmd)->redir;
		freelex(&cmdlex);
		if ((*cmd)->tab)
			free_tab((*cmd)->tab);
		if ((*cmd)->path)
			free((*cmd)->path);
		tmp = (*cmd)->next;
		free(*cmd);
		*cmd = tmp;
	}
}

void	resetshell(t_shell *shell)
{
	if (shell->cwd)
		free(shell->cwd);
	if (shell->inp)
		free(shell->inp);
	if (shell->newinp)
		free(shell->newinp);
	if (shell->finalinp)
		free(shell->finalinp);
	initinitinit(shell);
	shell->tmpexcode = shell->excode;
	shell->excode = 0;
	shell->lex = NULL;
	shell->cmd = NULL;
	shell->cwd = NULL;
}

void	resetloop(t_shell *shell)
{
	t_lex	*lex;
	t_cmd	*cmd;

	lex = shell->lex;
	cmd = shell->cmd;
	if (shell->tabpath)
		free_tab(shell->tabpath);
	freelex(&lex);
	freecmd(&cmd);
	resetshell(shell);
}
