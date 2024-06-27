/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:01:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 15:12:04 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_fds(t_fds *fd)
{
	fd->input = -42;
	fd->output = -42;
	fd->pipes[0] = -42;
	fd->pipes[1] = -42;
	fd->redir[1] = -42;
	fd->in = -42;
	fd->savedpipe = -42;
}

void	set_redirs(t_fds *fd)
{
	if (fd->pipes[1] != -42)
		fd->redir[1] = fd->pipes[1];
	if (fd->input != -42)
	{
		if (fd->redir[0] != -42 && !fd->prevpipe)
			close(fd->redir[0]);
		if (fd->prevpipe)
			fd->savedpipe = fd->redir[0];
		fd->redir[0] = fd->input;
	}
	if (fd->output != -42)
	{
		if (fd->pipes[1] != -42)
			close(fd->pipes[1]);
		fd->redir[1] = fd->output;
	}
}

void	close_fds_parent(t_fds *fd)
{
	if (fd->redir[0] != -42 && fd->redir[0] >= 0)
		close(fd->redir[0]);
	if (fd->redir[1] != -42 && fd->redir[1] >= 0)
		close(fd->redir[1]);
}

void	close_fds(t_fds *fd)
{
	if (!(fd->redir[0] == -42) && fd->redir[0] >= 0)
		close(fd->redir[0]);
	if (!(fd->redir[1] == -42) && fd->redir[1] >= 0)
		close(fd->redir[1]);
	if (fd->input != -42 && fd->input >= 0)
		close(fd->input);
	if (fd->output != -42 && fd->output >= 0)
		close(fd->output);
	if (!(fd->pipes[0] == -42) && fd->pipes[0] >= 0)
		close(fd->pipes[0]);
	if (!(fd->pipes[1] == -42) && fd->pipes[1] >= 0)
		close(fd->pipes[1]);
	if (!(fd->savedpipe == -42) && fd->savedpipe >= -1)
		close(fd->savedpipe);
}
