/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:23:32 by yabejani          #+#    #+#             */
/*   Updated: 2024/07/01 14:35:13 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_execpath(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, "PATH"))
			return (ft_split(env->value, ':'));
		env = env->next;
	}
	return (NULL);
}

int	withpath(t_shell *shell, t_cmd **c)
{
	struct stat	info;

	if (ft_strchr((*c)->tab[0], '/') && access((*c)->tab[0], F_OK | X_OK) != 0)
	{
		shell->excode = 127;
		(*c)->pathnoaccess = true;
		*c = (*c)->next;
		return (1);
	}
	else if (ft_strchr((*c)->tab[0], '/') && access((*c)->tab[0],
			F_OK | X_OK) == 0)
	{
		if (stat((*c)->tab[0], &info) == 0 && S_ISDIR(info.st_mode))
		{
			ft_perror(shell, (*c)->tab[0], "Is a directory", NULL);
			shell->excode = 126;
			(*c)->pathnoaccess = true;
		}
		(*c)->path = ft_strdup((*c)->tab[0]);
		if (!(*c)->path)
			exitmsg(shell, MERROR);
		*c = (*c)->next;
		return (1);
	}
	return (0);
}

static void	set_cmd_path(t_shell *shell, t_cmd *c, char *tmp, int *flag)
{
	free(c->tab[0]);
	c->tab[0] = ft_strdup(tmp);
	if (!c->tab[0])
		(free(tmp), c->tab[0] = NULL, exitmsg(shell, MERROR));
	c->path = ft_strdup(tmp);
	if (!c->path)
		(free(tmp), exitmsg(shell, MERROR));
	(*flag) = 1;
}

static void	set_path_anyway(t_shell *shell, t_cmd *c)
{
	if (c->path)
		(free(c->path), c->path = NULL);
	shell->excode = 127;
	c->path = ft_strdup(c->tab[0]);
	if (!c->path)
		exitmsg(shell, MERROR);
}

void	handle_withpath(t_shell *shell, t_cmd *c, int i, int flag)
{
	char	*tmp;

	while (c)
	{
		i = -1;
		if (c->tab[0])
		{
			if (withpath(shell, &c))
				continue ;
			flag = 0;
			while (shell->tabpath && shell->tabpath[++i])
			{
				tmp = ft_strjoinfree(ft_strjoin(shell->tabpath[i], "/"),
						c->tab[0]);
				if (!tmp)
					exitmsg(shell, MERROR);
				if (access(tmp, X_OK) == 0)
					set_cmd_path(shell, c, tmp, &flag);
				(free(tmp), tmp = NULL);
			}
			if (!flag && c->builtin == NOT)
				set_path_anyway(shell, c);
		}
		c = c->next;
	}
}
