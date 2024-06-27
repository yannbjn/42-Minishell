/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:18:59 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:24:13 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_pwd(t_shell *shell)
{
	char	*tmp;
	t_env	*new;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		exitmsg(shell, MERROR);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		(free(tmp), exitmsg(shell, MERROR));
	new->key = ft_strdup("PWD");
	if (!new->key)
		(free(tmp), exitmsg(shell, MERROR));
	new->value = ft_strdup(tmp);
	if (!new->value)
		(free(tmp), exitmsg(shell, MERROR));
	new->index = 1;
	new->next = NULL;
	new->prev = NULL;
	shell->env = new;
}

void	set_shlvl(t_shell *shell)
{
	t_env	*curr;
	t_env	*new;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exitmsg(shell, MERROR);
	new->key = ft_strdup("SHLVL");
	if (!new->key)
		exitmsg(shell, MERROR);
	new->value = ft_strdup("1");
	if (!new->value)
		exitmsg(shell, MERROR);
	new->index = 2;
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
}

void	set_lastcmd(t_shell *shell)
{
	t_env	*curr;
	t_env	*new;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exitmsg(shell, MERROR);
	new->key = ft_strdup("_");
	if (!new->key)
		exitmsg(shell, MERROR);
	new->value = ft_strdup("./minishell");
	if (!new->value)
		exitmsg(shell, MERROR);
	new->index = 3;
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
}

void	set_oldpwd(t_shell *shell)
{
	t_env	*curr;
	t_env	*new;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exitmsg(shell, MERROR);
	new->key = ft_strdup("OLDPWD");
	if (!new->key)
		exitmsg(shell, MERROR);
	new->value = ft_strdup("OLDPWD");
	new->index = 4;
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
	new->isunset = true;
	new->oldpwd = true;
}

void	ft_no_env(t_shell *shell)
{
	set_pwd(shell);
	set_shlvl(shell);
	set_lastcmd(shell);
	set_oldpwd(shell);
}
