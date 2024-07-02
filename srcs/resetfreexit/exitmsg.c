/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitmsg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:32:20 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/29 17:29:51 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_perror(t_shell *shell, char *word, char *msg, char *third)
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
		printf("minishell: %s: %s: %s\n", word, msg, third);
	else
		printf("minishell: %s: %s\n", word, msg);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		shell->excode = 1;
		(close(saved_stdout), perror("dup2"), exitmsg(shell, NULL));
	}
	close(saved_stdout);
}

void	freeenv(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		tmp = (*env)->next;
		free(*env);
		*env = tmp;
	}
}

void	ft_freeshell(t_shell *shell)
{
	t_env	*env;
	t_lex	*lex;
	t_cmd	*cmd;

	lex = shell->lex;
	cmd = shell->cmd;
	if (shell->tabpath)
		free_tab(shell->tabpath);
	if (shell->envp)
		free_tab(shell->envp);
	freelex(&lex);
	freecmd(&cmd);
	env = shell->env;
	free(shell->path->pwd);
	free(shell->path->oldpwd);
	free(shell->path);
	freeenv(&env);
	resetshell(shell);
}

void	exitmsg(t_shell *shell, char *errmsg)
{
	int	ext;

	ext = shell->excode;
	if (errmsg)
		perror(errmsg);
	ft_freeshell(shell);
	exit(ext);
}
