/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:32:15 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/24 14:16:34 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (cmd->tab[1])
	{
		ft_perror(shell, cmd->tab[1], NOSUCH, NULL);
		ft_freeshell(shell);
		exit(127);
	}
	i = 0;
	while (shell->envp[i])
		fd_printf(1, "%s\n", shell->envp[i++]);
	ft_freeshell(shell);
	exit(0);
}
