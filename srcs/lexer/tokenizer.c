/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:23 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/29 18:04:08 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	assign_enum(t_lex *new)
{
	if (ft_strictcmp(new->word, "|"))
		new->token = PIPE;
	if (ft_strictcmp(new->word, ">"))
		new->token = GREATER;
	if (ft_strictcmp(new->word, ">>"))
		new->token = D_GREATER;
	if (ft_strictcmp(new->word, "<"))
		new->token = LOWER;
	if (ft_strictcmp(new->word, "<<"))
		new->token = D_LOWER;
}

void	is_redir(t_shell *shell)
{
	t_lex	*new;

	new = shell->lex;
	while (new)
	{
		if (new->istoken && new->token != PIPE)
			new->isred = true;
		if (new->prev)
			if (new->prev->isred && new->prev->istoken)
				new->isred = true;
		new = new->next;
	}
}

static void	link_lex_nodes(t_shell *shell, t_lex *new, int *i, int *j)
{
	t_lex	*curr;

	curr = shell->lex;
	fill_lex_nodes(shell, new, i, j);
	new->next = NULL;
	if (!curr)
	{
		new->prev = NULL;
		shell->lex = new;
	}
	else
	{
		while (curr->next)
		{
			if (curr->next->prev != curr)
				curr->next->prev = curr;
			curr = curr->next;
		}
		curr->next = new;
		new->prev = curr;
	}
}

void	tokenizer(t_shell *shell)
{
	int		i;
	int		j;
	t_lex	*new;
	char	*str;

	i = 0;
	str = shell->finalinp;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			new = ft_calloc(1, sizeof(t_lex));
			if (!new)
				exitmsg(shell, MERROR);
			j = i;
			link_lex_nodes(shell, new, &i, &j);
			i = j;
		}
	}
}
