/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:08:58 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:53:30 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*is_num(t_shell *shell, char *str, int j)
{
	char	*befdoll;

	befdoll = ft_strndup(str, j - 1);
	if (!befdoll)
		exitmsg(shell, MERROR);//problemes de leaks ici tres certainement faire comme dans le expand du heredoc
	if (str[j] == '0')
		return (ftsjb(befdoll, ft_strjoin("bash", str + j + 1)));
	return (ft_strjoinfree(befdoll, str + j + 1));
}

char	*is_not_alnum(t_shell *shell, char *str, int j)
{
	char	*ext;
	char	*befdoll;

	ext = ft_itoa(shell->tmpexcode);
	if (!ext)
		exitmsg(shell, MERROR);//problemes de leaks ici tres certainement faire comme dans le expand du heredoc
	befdoll = ft_strndup(str, j - 1);
	if (!befdoll)
		exitmsg(shell, MERROR);//problemes de leaks ici tres certainement faire comme dans le expand du heredoc
	if (str[j] == '?')
		return (ftsjb(befdoll, ft_strjoinfree(ext, str + j + 1)));
	else if (str[j] == '\'')
		return (free(ext), ft_strjoinfree(befdoll, str + j));
	else
		return (free(ext), ft_strjoinfree(befdoll, str + j - 1));
}

void	handle_quotes(char c, t_flags *flags)
{
	if (c == '\"' && !flags->quoterotie)
		flags->quoterotie = true;
	else if (c == '\"' && flags->quoterotie)
		flags->quoterotie = false;
	else if (c == '\'' && !flags->entrecote)
		flags->entrecote = true;
	else if (c == '\'' && flags->entrecote)
		flags->entrecote = false;
}

void	handle_d_lower(char *tmp, t_flags *flags)
{
	if (tmp[flags->i] == '<' && tmp[flags->i - 1] == '<' && !flags->quoterotie)
	{
		flags->flag = true;
		tmp[flags->i - 1] *= -1;
		tmp[flags->i] *= -1;
		flags->i++;
		while (tmp[flags->i] == ' ')
			flags->i++;
		if (tmp[flags->i] == '\'' || tmp[flags->i] == '\"')
			flags->entrentrecote = true;
		if (flags->entrentrecote)
			while (tmp[flags->i] && tmp[flags->i] != '\''
				&& tmp[flags->i] != '\"' && tmp[flags->i] > 0)
				tmp[flags->i++] *= -1;
		else
			while (tmp[flags->i] && tmp[flags->i] != ' '
				&& tmp[flags->i] != '\0')
				tmp[flags->i++] *= -1;
	}
}

char	*expand_dollar(t_shell *shell, char *str, t_flags *flags, t_env *node)
{
	char	*key;
	char	*bdoll;
	int		j;

	j = flags->i + 1;
	if (ft_isdigit(str[j]))
		return (is_num(shell, str, j));
	if (!ft_isalnum(str[j]) && str[j] != '_')
	{
		str[flags->i] *= -1;
		return (is_not_alnum(shell, str, j));
	}
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	key = ft_strndup(str + flags->i + 1, j - flags->i - 1);
	bdoll = ft_strndup(str, flags->i);
	if (!key)
		exitmsg(shell, MERROR);
	while (node)
	{
		if (ft_strictcmp(node->key, key))
			return (free(key), ftsjb(bdoll, ft_strjoin(node->value, str + j)));
		node = node->next;
	}
	return (free(key), ft_strjoinfree(bdoll, str + j));
}
