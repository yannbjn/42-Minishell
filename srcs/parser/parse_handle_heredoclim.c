/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_heredoclim.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:37:14 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:45:23 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*trimquotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc((ft_strlen(str) - count_char(str) + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	if (new[j] != '\0')
		j++;
	new[j] = '\0';
	return (new);
}

static void	trimcmdtab(t_shell *shell, char **tab)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tab[++i])
	{
		tmp = trimquotes(tab[i]);
		if (!tmp)
			exitmsg(shell, MERROR);
		free(tab[i]);
		tab[i] = ft_strdup(tmp);
		if (!tab[i])
			exitmsg(shell, MERROR);
		free(tmp);
	}
}

static void	setquotelimflag(t_shell *shell, t_lex *redir)
{
	char	*tmp;

	if (checkifquotes(redir->next->word))
		redir->quotelim = true;
	tmp = trimquotes(redir->next->word);
	if (!tmp)
		exitmsg(shell, MERROR);
	free(redir->next->word);
	redir->next->word = ft_strdup(tmp);
	if (!redir->next->word)
		(free(tmp), exitmsg(shell, MERROR));
	free(tmp);
	redir = redir->next;
}

static void	quotedeporc(t_shell *shell, t_lex *redir)
{
	char	*tmp;

	tmp = trimquotes(redir->word);
	if (!tmp)
		exitmsg(shell, MERROR);
	free(redir->word);
	redir->word = ft_strdup(tmp);
	if (!redir->word)
		(free(tmp), exitmsg(shell, MERROR));
	free(tmp);
}

void	notrimherelim(t_shell *shell)
{
	t_cmd	*cmd;
	t_lex	*redir;

	cmd = shell->cmd;
	while (cmd)
	{
		trimcmdtab(shell, cmd->tab);
		redir = cmd->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
				setquotelimflag(shell, redir);
			else
				quotedeporc(shell, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
