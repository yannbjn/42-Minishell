/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:32:28 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:43:40 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	count_char(char *str)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c++;
		i++;
	}
	return (c);
}

int	checkifquotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	return (0);
}

void	backtoascii(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;
	t_lex	*redir;

	cmd = shell->cmd;
	while (cmd)
	{
		i = -1;
		cmd->pathnoaccess = false;
		while (cmd->tab[++i])
			pos_quotes(cmd->tab[i]);
		redir = cmd->redir;
		while (redir)
		{
			i = -1;
			if (redir->word)
				while (redir->word[++i])
					if (redir->word[i] < 0)
						redir->word[i] *= -1;
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
