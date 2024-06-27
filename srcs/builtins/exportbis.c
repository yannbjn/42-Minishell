/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportbis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:22:30 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/21 18:30:37 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_envp(t_shell *shell)
{
	if (shell->envp != NULL)
		free_tab(shell->envp);
	fill_envp(shell);
}

void	exp_append_toenv(t_shell *shell, t_env *env, t_env *new, t_export *exp)
{
	free(env->value);
	env->value = ft_strdup(exp->value);
	env->isunset = false;
	if (!env->value)
		(free(new), free(exp->value), free(exp->key), exitmsg(shell, MERROR));
	free(new);
}

void	exp_addback_toenv(t_shell *shell, t_env *env, t_env *new, t_export *exp)
{
	env->next = new;
	new->prev = env;
	new->next = NULL;
	new->key = ft_strdup(exp->key);
	new->isunset = false;
	if (!new->key)
		(free(new), free(exp->value), free(exp->key), exitmsg(shell, MERROR));
	new->value = ft_strdup(exp->value);
	if (!new->value)
		(free(new), free(exp->value), free(exp->key), exitmsg(shell, MERROR));
}

void	add_toenv(t_shell *shell, t_export *exp)
{
	t_env	*env;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		(free(new), free(exp->key), free(exp->value), exitmsg(shell, MERROR));
	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, exp->key))
		{
			exp_append_toenv(shell, env, new, exp);
			break ;
		}
		if (!env->next)
		{
			exp_addback_toenv(shell, env, new, exp);
			break ;
		}
		env = env->next;
	}
	(free(exp->value), free(exp->key));
	update_envp(shell);
}
