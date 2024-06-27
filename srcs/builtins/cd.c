/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:16:09 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:25:15 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_checkdir(t_shell *shell, t_cmd *cmd)
{
	DIR	*dir;

	dir = opendir(cmd->tab[1]);
	if (!dir)
	{
		fd_printf(2, "minishell: cd: %s: ", cmd->tab[1]);
		perror(NULL);
		shell->excode = 1;
		return (0);
	}
	closedir(dir);
	return (1);
}

void	ft_updateoldpwd(t_shell *shell, char *tmp)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, "OLDPWD"))
		{
			free(env->value);
			env->value = ft_strdup(tmp);
			if (env->isunset && env->oldpwd)
			{
				env->isunset = false;
				env->oldpwd = false;
			}
		}
		if (ft_strictcmp(env->key, "PWD"))
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
		}
		env = env->next;
	}
	free(tmp);
}

void	ft_cdexec(t_shell *shell, char *dirname)
{
	char	*tmp;
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, "PWD"))
			tmp = ft_strdup(env->value);
		env = env->next;
	}
	if (chdir(dirname) == -1)
	{
		perror("chdir");
		shell->excode = 1;
		return ;
	}
	ft_updateoldpwd(shell, tmp);
	update_envp(shell);
}

void	ft_cdhome(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, "HOME"))
			break ;
		if (!env->next)
		{
			fd_printf(2, "minishell: cd: HOME not set\n");
			shell->excode = 1;
			return ;
		}
		env = env->next;
	}
	ft_cdexec(shell, env->value);
}

void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->tab[1] && cmd->tab[2])
	{
		printf("minishell: cd: too many arguments\n");
		shell->excode = 1;
		return ;
	}
	if (cmd->tab[1])
		if (!ft_checkdir(shell, cmd))
			return ;
	if (cmd->next || cmd->prev)
		return ;
	if (!cmd->tab[1])
		ft_cdhome(shell);
	else
		ft_cdexec(shell, cmd->tab[1]);
}
