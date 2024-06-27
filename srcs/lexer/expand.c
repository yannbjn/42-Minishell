/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:21:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:15:38 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_dollar_expansion(t_shell *shell, char **tmp, char **tmptmp,
		t_flags *flags)
{
	int	len;

	len = ft_strlen(*tmp);
	if (flags->i <= len && (*tmp)[flags->i] == '$' && !flags->entrecote
		&& !flags->flag)
	{
		free(*tmptmp);
		*tmptmp = ft_strdupfree(expand_dollar(shell, *tmp, flags, shell->env));
		free(*tmp);
		*tmp = ft_strdup(*tmptmp);
		if (!(*tmp))
			exitmsg(shell, MERROR);
		flags->i = 0;
	}
}

static char	*cleanup_and_return(char *tmp, char *tmptmp)
{
	free(tmp);
	return (tmptmp);
}

static void	initialize_flags(t_flags *flags)
{
	flags->entrecote = false;
	flags->quoterotie = false;
	flags->flag = false;
	flags->entrentrecote = false;
	flags->i = -1;
}

static char	*diggin_for_dollarzbis(t_shell *shell, char *tmp, char *tmptmp)
{
	t_flags	flags;
	int		len;

	initialize_flags(&flags);
	len = ft_strlen(tmp);
	while (++flags.i <= len)
	{
		len = ft_strlen(tmp);
		handle_quotes(tmp[flags.i], &flags);
		if (flags.i > 0 && tmp[flags.i] == '<')
			handle_d_lower(tmp, &flags);
		handle_dollar_expansion(shell, &tmp, &tmptmp, &flags);
	}
	return (cleanup_and_return(tmp, tmptmp));
}

void	expander(t_shell *shell)
{
	char	*tmp;
	char	*tmptmp;

	shell->inp = pos_no_quotes(shell->inp);
	tmp = ft_strdup(shell->inp);
	if (!tmp)
		exitmsg(shell, MERROR);
	tmptmp = ft_strdup(shell->inp);
	if (!tmptmp)
		(free(tmp), exitmsg(shell, MERROR));
	shell->newinp = ft_strdupfree(diggin_for_dollarzbis(shell, tmp, tmptmp));
	if (!shell->newinp)
		exitmsg(shell, MERROR);
}
