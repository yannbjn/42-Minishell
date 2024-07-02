/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:19:41 by yabejani          #+#    #+#             */
/*   Updated: 2024/07/02 13:27:09 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	eperr(t_shell *shell, char *word, char *msg, char *third)
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

void	init_export_struct(t_export *exp)
{
	exp->value = NULL;
	exp->key = NULL;
	exp->i = -1;
	exp->flag = 0;
}

int	ft_expbefkey(t_shell *shell, t_cmd *cmd, t_export *exp)
{
	if (!isalpha(cmd->tab[exp->h][0]) && !exp->flag)
	{
		eperr(shell, E, cmd->tab[exp->h], NOTV);
		return (shell->excode = 1, 0);
	}
	else if (!ft_isalnum(cmd->tab[exp->h][exp->i])
		&& cmd->tab[exp->h][exp->i] != '=' && !exp->flag)
	{
		eperr(shell, E, cmd->tab[exp->h], NOTV);
		return (shell->excode = 1, 0);
		exp->i++;
	}
	else if (cmd->tab[exp->h][exp->i] == '=' && !exp->flag)
	{
		exp->flag = 1;
		exp->key = ft_strndup(cmd->tab[exp->h], exp->i++);
		if (!exp->key)
			exitmsg(shell, MERROR);
		else if (!exp->key[0])
		{
			return (eperr(shell, E, cmd->tab[exp->h], NOTV), free(exp->key), 0);
			shell->excode = 1;
		}
	}
	return (1);
}

void	check_if_addtoenv(t_shell *shell, t_cmd *cmd, t_export *exp)
{
	if (cmd->next || cmd->prev)
	{
		(free(exp->key), free(exp->value));
		return ;
	}
	if (exp->flag)
		add_toenv(shell, exp);
}

void	ft_export(t_shell *shell, t_cmd *cmd)
{
	t_export	exp;

	exp.h = 0;
	if (!cmd->tab[1])
		return ;
	while (cmd->tab[++exp.h])
	{
		init_export_struct(&exp);
		while (cmd->tab[exp.h][++exp.i])
		{
			if (!ft_expbefkey(shell, cmd, &exp))
				return ;
			if (exp.flag)
			{
				exp.j = exp.i;
				while (cmd->tab[exp.h][exp.j])
					exp.j++;
				exp.value = ft_strndup(cmd->tab[exp.h] + exp.i, exp.j);
				if (!exp.value)
					(free(exp.key), exitmsg(shell, MERROR));
				break ;
			}
		}
		check_if_addtoenv(shell, cmd, &exp);
	}
}

// flag pour le unset ou pas dasn t_env pour savoir si print
// gnagnagna gnagnagna gnagnagna je trouve tjrs des pbs je m'appelle Jules
// gnagnagna changer le join pour envp null \0 gnagnagna pas /0 mais \0