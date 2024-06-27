/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:06:30 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/21 18:37:30 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int		i;
	t_env	*env;

	i = 1;
	if (cmd->prev || cmd->next || !cmd->tab[1])
		return ;
	while (cmd->tab[i])
	{
		env = shell->env;
		while (env)
		{
			if (ft_strictcmp(env->key, cmd->tab[i]))
			{
				if (env->value)
					free(env->value);
				env->value = NULL;
				env->isunset = true;
			}
			env = env->next;
		}
		i++;
	}
	update_envp(shell);
}
