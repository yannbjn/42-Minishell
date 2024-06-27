/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:52:02 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/21 18:36:20 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exit_args(t_cmd *cmd, int *flag)
{
	int	i;

	i = 0;
	if (!ft_isdigit(cmd->tab[1][0]) && cmd->tab[1][0] != '+'
		&& cmd->tab[1][0] != '-')
	{
		fd_printf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->tab[1]);
		(*flag) = 1;
		return (2);
	}
	while (cmd->tab[1][++i])
	{
		if (!ft_isdigit(cmd->tab[1][i]) && !(*flag))
		{
			fd_printf(2, "minishell: exit: %s: numeric argument required\n",
				cmd->tab[1]);
			(*flag) = 1;
			return (2);
		}
	}
	return (ft_atoi(cmd->tab[1]) % 256);
}

void	ft_exit(t_shell *shell, t_cmd *cmd, t_fds *fd)
{
	int	ext;
	int	flag;

	flag = 0;
	if (cmd->tab[1])
		shell->tmpexcode = exit_args(cmd, &flag);
	if (cmd->tab[1] && cmd->tab[2] && !flag)
	{
		fd_printf(2, "minishell: exit: too many arguments\n");
		fd_printf(1, "exit\n");
		shell->excode = 1;
		shell->tmpexcode = 1;
		return ;
	}
	if (cmd->next || cmd->prev)
		return ;
	ext = shell->tmpexcode;
	ft_freeshell(shell);
	close_fds(fd);
	fd_printf(1, "exit\n");
	exit(ext);
}
// a verifier le fd_printf in stdout