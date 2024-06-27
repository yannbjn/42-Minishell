/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:47:37 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:23:36 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_shlvl(t_shell *shell, t_env *node)
{
	int		shlvl;
	char	*byte;

	shlvl = ft_atoi(node->value);
	free(node->value);
	node->value = NULL;
	byte = ft_itoa(shlvl + 1);
	if (!byte)
		exitmsg(shell, MERROR);
	node->value = ft_strdupfree(byte);
	if (!node->value)
		exitmsg(shell, MERROR);
}

static void	get_key_env(t_shell *shell, t_env *node, char **envp, int i)
{
	int	j;
	int	lim;

	j = -1;
	lim = 0;
	while (envp[i][++j])
		if (!lim && envp[i][j] == '=')
			lim = j;
	node->key = ft_calloc(lim + 1, sizeof(char));
	if (!node->key)
		exitmsg(shell, MERROR);
	ft_strncpy(node->key, envp[i], lim);
	node->value = ft_strdup(getenv(node->key));
	if (ft_strictcmp(node->key, "SHLVL"))
		set_shlvl(shell, node);
}

static void	init_env_nodes(t_shell *shell, t_env *newnode, char **envp, int i)
{
	t_env	*curr;

	curr = shell->env;
	newnode->index = i;
	get_key_env(shell, newnode, envp, i);
	newnode->isunset = false;
	newnode->next = NULL;
	newnode->oldpwd = false;
	if (!curr)
	{
		newnode->prev = NULL;
		shell->env = newnode;
	}
	else
	{
		while (curr->next)
		{
			if (curr->next->prev != curr)
				curr->next->prev = curr;
			curr = curr->next;
		}
		curr->next = newnode;
		newnode->prev = curr;
	}
}

void	ft_getenv(t_shell *shell, char **envp)
{
	t_env	*newnode;
	int		i;

	i = 0;
	shell->envp = NULL;
	shell->tmpexcode = 0;
	if (!envp || !envp[i])
	{
		ft_no_env(shell);
		return ;
	}
	while (envp && envp[i])
	{
		newnode = malloc(sizeof(t_env));
		if (!newnode)
			exitmsg(shell, MERROR);
		init_env_nodes(shell, newnode, envp, i);
		i++;
	}
}
