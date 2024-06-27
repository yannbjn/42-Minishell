/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:41:27 by jfita             #+#    #+#             */
/*   Updated: 2024/06/27 14:06:58 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_open_quotes(t_shell *shell, char *input, int flag)
{
	char	quote;
	int		i;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\"' || input[i] == '\'') && (!flag))
		{
			quote = input[i];
			flag = 1;
		}
		else if (flag && input[i] != quote)
			input[i] *= -1;
		else if (flag == 1 && input[i] == quote)
			flag = 0;
	}
	if (flag == 1)
	{
		ft_perror(shell, "Invalid syntax", "unclosed quotes", NULL);
		shell->excode = 2;
	}
	shell->inp = ft_strdup(input);
	if (!shell->inp)
		(free(input), exitmsg(shell, MERROR));
}

void	lexer(t_shell *shell, char *input)
{
	t_lex	*cpy;

	check_open_quotes(shell, input, 0);
	expander(shell);
	free(shell->inp);
	renegentrecote(shell, -1);
	shell->finalinp = ft_strdup(shell->inp);
	if (!shell->finalinp)
		exitmsg(shell, MERROR);
	tokenizer(shell);
	cpy = shell->lex;
	check_syntax(shell, cpy, 0);
	is_redir(shell);
}

// free input PITIE PENSER A FREE INPUT DANS WHILE 
// (1) par rapport a addhistory ne pas le free ici

// on parcours la chaine
// si ya une quote et que flag = 0, flag interquotes = 1
//  while interquote
// str[i] *=-1
// si quote && flag = 1
// flag = 0
// " ' ' "
// ' " " '

// free input PITIE PENSER A FREE INPUT DANS WHILE (1)