/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:13:50 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 15:19:35 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*is_numm(char *str, int j)
{
	char	*befdoll;

	befdoll = ft_strndup(str, j - 1);
	if (!befdoll)
		return (NULL);
	if (str[j] == '0')
		return (ftsjb(befdoll, ft_strjoin("bash", str + j + 1)));
	return (ft_strjoinfree(befdoll, str + j + 1));
}

static char	*is_not_alnumm(t_shell *shell, char *str, int j)
{
	char	*ext;
	char	*befdoll;

	ext = ft_itoa(shell->excode);
	if (!ext)
		return (NULL);
	befdoll = ft_strndup(str, j - 1);
	if (!befdoll)
		return (free(ext), NULL);
	if (str[j] == '?')
		return (ftsjb(befdoll, ft_strjoinfree(ext, str + j + 1)));
	else if (str[j] == '\'')
		return (free(ext), ft_strjoinfree(befdoll, str + j));
	else
		return (free(ext), ft_strjoinfree(befdoll, str + j - 1));
}

static char	*expand_hdollar(t_shell *shell, char *str, int *i, t_env *node)
{
	char	*key;
	int		j;
	char	*bdoll;

	j = (*i) + 1;
	if (ft_isdigit(str[j]))
		return (is_numm(str, j));
	if (!ft_isalnum(str[j]) && str[j] != '_')
	{
		str[(*i)] *= -1;
		return (is_not_alnumm(shell, str, j));
	}
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	key = ft_strndup(str + *i + 1, j - *i - 1);
	bdoll = ft_strndup(str, *i);
	if (!key)
		return (NULL);
	while (node)
	{
		if (ft_strictcmp(node->key, key))
			return (free(key), ftsjb(bdoll, ft_strjoin(node->value, str + j)));
		node = node->next;
	}
	return (free(key), ft_strjoinfree(bdoll, str + j));
}

static char	*diggin_for_here_dollarz(t_shell *shell, char *str, int i)
{
	char	*tmp;
	char	*tmptmp;

	tmp = ft_strdup(str);
	if (!tmp)
		(free(str), exitmsg(shell, MERROR));
	tmptmp = ft_strdup(str);
	if (!tmptmp)
		(free(str), free(tmp), exitmsg(shell, MERROR));
	while (tmp[++i])
	{
		if (tmp[i] == '$')
		{
			free(tmptmp);
			tmptmp = ft_strdupfree(expand_hdollar(shell, tmp, &i, shell->env));
			if (!tmptmp)
				return (free(tmp), NULL);
			free(tmp);
			tmp = ft_strdup(tmptmp);
			if (!tmp)
				exitmsg(shell, MERROR);
			i = -1;
		}
	}
	return (free(str), free(tmp), pos_quotes(tmptmp), ft_strdupfree(tmptmp));
}

int	here_doc_exp(t_shell *shell, t_cmd *cmd, t_lex *lex, t_fds *fd)
{
	int		tmp;
	char	*str;
	char	*exp;

	cmd->heredoc = ft_strdup("/tmp/.here_doc_a");
	if (!cmd->heredoc)
		exitmsg(shell, MERROR);
	hd_file(shell, cmd);
	tmp = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd->input = open(cmd->heredoc, O_RDONLY);
	fd->in = dup(STDIN_FILENO);
	str = readline("> ");
	while (str && !ft_strictcmp(lex->next->word, str))
	{
		exp = diggin_for_here_dollarz(shell, str, -1);
		if (!exp)
			(free(str), free(cmd->heredoc), close(tmp));
		write(tmp, exp, ft_strlen(exp));
		write(tmp, "\n", 1);
		free(exp);
		str = readline("> ");
	}
	ctrlc(shell, fd, cmd);
	return (close(tmp), free(str), free(cmd->heredoc), close(fd->in), 130);
}
