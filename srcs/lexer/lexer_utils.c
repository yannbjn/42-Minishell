/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:46:43 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/12 16:18:59 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_part_of_word(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == '\0')
		return (0);
	return (1);
}

static void	ft_skip_spaces(char *str, int *i, int *j)
{
	while (str[*j] == ' ')
	{
		(*j)++;
		*i = *j;
	}
}

static void	ftnotwrd(t_shell *shell, t_lex *new, int *i, int *j)
{
	char	*str;
	char	chevron;

	str = shell->finalinp;
	if (str[*j] == '<' || str[*j] == '>')
	{
		chevron = str[*j];
		if (str[*j + 1] == chevron)
			(*j)++;
		(*j)++;
		new->word = ft_strndup(str + *i, *j - *i);
		new->istoken = true;
		*i = *j;
	}
	else if (str[*j] == '|')
	{
		new->word = ft_strndup(str + *i, ++(*j) - *i);
		if (!new->word)
			exitmsg(shell, MERROR);
		*i = *j;
		new->istoken = true;
	}
	if (!new->word)
		exitmsg(shell, MERROR);
}

void	renegentrecote(t_shell *shell, int i)
{
	int		flag;
	char	quote;
	char	*new;

	flag = 0;
	new = ft_strdup(shell->newinp);
	if (!new)
		exitmsg(shell, MERROR);
	while (new[++i])
	{
		if ((new[i] == '\"' || new[i] == '\'') && (!flag))
		{
			quote = new[i];
			flag = 1;
		}
		else if (flag && new[i] != quote && new[i] > 0)
			new[i] *= -1;
		else if (flag == 1 && new[i] == quote)
			flag = 0;
	}
	shell->inp = ft_strdup(new);
	if (!shell->inp)
		(free(new), exitmsg(shell, MERROR));
	free(new);
}

void	fill_lex_nodes(t_shell *shell, t_lex *new, int *i, int *j)
{
	char	*str;

	str = shell->finalinp;
	if (is_part_of_word(str[*j]))
	{
		while (is_part_of_word(str[*j]))
			(*j)++;
		new->word = ft_strndup(str + *i, *j - *i);
		if (!new->word)
			exitmsg(shell, MERROR);
		*i = *j;
	}
	else if (!is_part_of_word(str[*j]))
	{
		ft_skip_spaces(str, i, j);
		ftnotwrd(shell, new, i, j);
		assign_enum(new);
	}
}

// else
// {
// 	new->word = ft_strdup(">");
// 	if (!new->word)
// 		exitmsg(shell, MERROR);
// 	++(*j);
// }