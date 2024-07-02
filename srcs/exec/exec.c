/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:28:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/07/01 14:34:21 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	children(t_shell *shell, t_cmd *cmd, t_fds *fd)
{
	if (fd->pipes[0] != -42)
		close(fd->pipes[0]);
	if (fd->savedpipe != -42)
		close(fd->savedpipe);
	if (fd->redir[0] != -42)
		if (dup2(fd->redir[0], STDIN_FILENO) == -1)
			(close_fds(fd), exitmsg(shell, NULL));
	if (fd->redir[1] != -42)
		if (dup2(fd->redir[1], STDOUT_FILENO) == -1)
			(close_fds(fd), exitmsg(shell, NULL));
	if (cmd->pathnoaccess)
	{
		if (!cmd->path)
			ft_perror(shell, cmd->tab[0], strerror(errno), NULL);
		close_fds(fd);
		exitmsg(shell, NULL);
	}
	else if (!cmd->path)
	{
		close_fds(fd);
		exitmsg(shell, NULL);
	}
	close_fds(fd);
	if (execve(cmd->path, cmd->tab, shell->envp) == -1)
		(ft_perror(shell, cmd->path, CMDFAIL, NULL), exitmsg(shell, NULL));
}

void	ft_exec(t_shell *shell, t_cmd *cmd, t_fds *fd)
{
	if (cmd->builtin == EXIT)
		ft_exit(shell, cmd, fd);
	else if (cmd->builtin == CD)
		ft_cd(shell, cmd);
	else if (cmd->builtin == EXPORT)
		ft_export(shell, cmd);
	else if (cmd->builtin == UNSET)
		ft_unset(shell, cmd);
	else
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			exitmsg(shell, "fork");
		if (cmd->pid == 0)
		{
			if (cmd->builtin != NOT)
				child_builtin(shell, cmd, fd);
			else
				children(shell, cmd, fd);
		}
		close_fds_parent(fd);
		fd->redir[0] = fd->pipes[0];
	}
}

void	ft_wait_child(t_shell *shell)
{
	int		status;
	t_cmd	*cmd;

	status = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->pid != -2 && cmd->pid != -1)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				shell->excode = WEXITSTATUS(status);
			if (errno == EACCES)
				shell->excode = 126;
			if (cmd->pid == -1)
				shell->excode = 127;
		}
		cmd = cmd->next;
	}
}

void	start_exec(t_shell *shell, t_cmd *cmd)
{
	t_fds	fd;

	prep_exec(shell, &fd);
	while (cmd)
	{
		init_fds(&fd);
		ft_pipes(shell, cmd, &fd);
		handle_redir(shell, cmd, &fd);
		if (shell->excode == 130)
			break ;
		set_redirs(&fd);
		if (!cmd->path && cmd->builtin == NOT)
			close_fds(&fd);
		if (cmd->tab[0])
			ft_exec(shell, cmd, &fd);
		if (!cmd->next)
			close_fds_parent(&fd);
		cmd = cmd->next;
	}
	(ft_wait_child(shell), close_fds(&fd));
}

void	launch_exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	start_exec(shell, cmd);
}
