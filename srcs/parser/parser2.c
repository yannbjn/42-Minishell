/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:53:13 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:35:55 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_tab(t_shell *shell, t_lex *lex, t_cmd *cmd)
{
	int		i;
	t_lex	*tmp;

	i = 0;
	tmp = lex;
	while (tmp && tmp->word && tmp->token != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	cmd->tab = ft_calloc(i + 1, sizeof(char *));
	if (!cmd->tab)
		exitmsg(shell, MERROR);
}

void	split_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	t_lex	*lex;
	int		i;

	cmd = shell->cmd;
	lex = shell->lex;
	while (cmd)
	{
		i = 0;
		init_tab(shell, lex, cmd);
		while (lex && lex->word && lex->token != PIPE)
		{
			cmd->tab[i] = ft_strdup(lex->word);
			if (!cmd->tab[i])
				exitmsg(shell, MERROR);
			lex = lex->next;
			i++;
		}
		cmd->tab[i] = NULL;
		if (lex && lex->next && lex->word && lex->token == PIPE)
			lex = lex->next;
		cmd = cmd->next;
	}
}
