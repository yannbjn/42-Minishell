/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:07:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/28 14:50:09 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*getpath(t_shell *shell, char *key)
{
	t_env	*envnode;

	envnode = shell->env;
	while (envnode)
	{
		if (ft_strictcmp(envnode->key, key) != 0)
			break ;
		envnode = envnode->next;
	}
	if (!envnode)
		return (NULL);
	return (envnode->value);
}

static int	env_size(t_shell *shell)
{
	t_env	*node;
	int		len;

	len = 0;
	node = shell->env;
	while (node)
	{
		if (node->key)
			len++;
		node = node->next;
	}
	return (len);
}

char	*ft_sjfs(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s2);
	return (str);
}

void	fill_envp(t_shell *shell)
{
	int		len;
	int		i;
	t_env	*curr;

	i = 0;
	len = env_size(shell);
	curr = shell->env;
	shell->envp = NULL;
	if (shell->envp != NULL)
		free_tab(shell->envp);
	shell->envp = NULL;
	shell->envp = ft_calloc(len + 1, sizeof(char *));
	if (!shell->envp)
		exitmsg(shell, MERROR);
	while (curr)
	{
		if (curr->key && !curr->isunset)
		{
			shell->envp[i] = ft_sjfs(curr->key, ft_strjoin("=", curr->value));
			if (!shell->envp[i])
				exitmsg(shell, MERROR);
			i++;
		}
		curr = curr->next;
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	char	*str;

	shell->env = NULL;
	shell->lex = NULL;
	shell->cmd = NULL;
	shell->excode = 0;
	shell->path = ft_calloc(1, sizeof(t_path));
	if (!shell->path)
		exitmsg(shell, MERROR);
	ft_getenv(shell, envp);
	fill_envp(shell);
	str = getpath(shell, "PWD");
	if (str)
	{
		shell->path->pwd = ft_strdup(str);
		if (!shell->path->pwd)
			exitmsg(shell, MERROR);
	}
	str = getpath(shell, "OLDPWD");
	if (str)
	{
		shell->path->oldpwd = ft_strdup(str);
		if (!shell->path->oldpwd)
			exitmsg(shell, MERROR);
	}
}
