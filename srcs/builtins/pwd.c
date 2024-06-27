/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:36:02 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/24 14:16:53 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pwdperror(t_shell *shell, char *word, char *msg, char *third)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		shell->excode = 1;
		(perror("dup"), exitmsg(shell, NULL));
	}
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		shell->excode = 1;
		(close(saved_stdout), perror("dup2"), exitmsg(shell, NULL));
	}
	if (third)
		printf("minishell: %s: '%s': %s\n", word, msg, third);
	else
		printf("minishell: %s: %s\n", word, msg);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		shell->excode = 1;
		(close(saved_stdout), perror("dup2"), exitmsg(shell, NULL));
	}
	close(saved_stdout);
}

void	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
	else if (cmd->tab[1] && cmd->tab[1][0] == '-')
	{
		pwdperror(shell, "pwd", cmd->tab[1], "invalid option");
		free(pwd);
		ft_freeshell(shell);
		exit(2);
	}
	else
		fd_printf(1, "%s\n", pwd);
	free(pwd);
	ft_freeshell(shell);
	exit(0);
}
