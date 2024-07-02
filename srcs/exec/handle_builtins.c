/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:58:27 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/28 14:19:49 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == ECHO)
		ft_echo(shell, cmd);
	if (cmd->builtin == ENV)
		ft_env(shell, cmd);
	if (cmd->builtin == PWD)
		ft_pwd(shell, cmd);
}

void	child_builtin(t_shell *shell, t_cmd *cmd, t_fds *fd)
{
	if (fd->savedpipe != -42)
		close(fd->savedpipe);
	if (fd->pipes[0] != -42)
		close(fd->pipes[0]);
	if (fd->redir[0] != -42)
		if (dup2(fd->redir[0], STDIN_FILENO) == -1)
			(close_fds(fd), exitmsg(shell, NULL));
	if (fd->redir[1] != -42)
		if (dup2(fd->redir[1], STDOUT_FILENO) == -1)
			(close_fds(fd), exitmsg(shell, NULL));
	close_fds(fd);
	exec_builtin(shell, cmd);
}

void	check_builtins(t_cmd *cmd)
{
	if (ft_strictcmp(cmd->tab[0], "echo"))
		cmd->builtin = ECHO;
	if (ft_strictcmp(cmd->tab[0], "cd"))
		cmd->builtin = CD;
	if (ft_strictcmp(cmd->tab[0], "pwd"))
		cmd->builtin = PWD;
	if (ft_strictcmp(cmd->tab[0], "export"))
		cmd->builtin = EXPORT;
	if (ft_strictcmp(cmd->tab[0], "unset"))
		cmd->builtin = UNSET;
	if (ft_strictcmp(cmd->tab[0], "env"))
		cmd->builtin = ENV;
	if (ft_strictcmp(cmd->tab[0], "exit"))
		cmd->builtin = EXIT;
}
