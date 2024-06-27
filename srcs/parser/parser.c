/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:25 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:37:53 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	getlastcmd(t_shell *shell, t_env *env, t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		if (!cmd->next)
		{
			while (cmd->tab[i])
			{
				if (!cmd->tab[i + 1])
				{
					if (env->value)
						free(env->value);
					env->value = ft_strdup(cmd->tab[i]);
					if (!env->value)
						exitmsg(shell, MERROR);
					return ;
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}

void	updatelastcmd(t_shell *shell)
{
	t_env	*env;
	t_cmd	*cmd;

	cmd = shell->cmd;
	env = shell->env;
	while (env)
	{
		if (ft_strictcmp(env->key, "_"))
			getlastcmd(shell, env, cmd);
		env = env->next;
	}
}

void	parser(t_shell *shell)
{
	shell->cmd = split_redir(shell, &shell->lex);
	split_cmd(shell);
	notrimherelim(shell);
	backtoascii(shell);
	updatelastcmd(shell);
}

// t_cmd	*node;
// t_lex	*redir;
// int	i;
// int	j;

// i = 0;
// node = shell->cmd;
// while (node)
// {
// 	printf("index cmd = %d\n", i++);
// 	redir = node->redir;
// 	j = -1;
// 	while (node->tab[++j])
// 		printf("tab[%d] = %s\n", j, node->tab[j]);
// 	while (redir)
// 	{
// 		printf("%s\n", redir->word);
// 		redir = redir->next;
// 	}
// 	node = node->next;
// }

// while (node)
// {
// 	printf("index cmd = %d\n", i++);
// 	redir = node->redir;
// 	while (redir)
// 	{
// 		printf("%s\n", redir->word);
// 		redir = redir->next;
// 	}
// 	node = node->next;
// }
// printf("Original list values: ");
// temp = shell->lex;
// while (temp != NULL)
// {
// 	printf("%s ", temp->word);
// 	temp = temp->next;
// }
// printf("\n");
// static void	notrimhere(t_shell *shell)
// {
// 	int		i;
// 	t_cmd 	*cmd;
// 	t_lex 	*redir;
// 	char 	*tmp;

// 	cmd = shell->cmd;
// 	while (cmd)
// 	{
// 		i = -1;
// 		while (cmd->tab[++i])
// 		{
// 			tmp = trimquotes(cmd->tab[i]);
// 			if (!tmp)
// 				exitmsg(shell, MERROR);
// 			free(cmd->tab[i]);
// 			cmd->tab[i] = ft_strdup(tmp);
// 			if (!cmd->tab[i])
// 				exitmsg(shell, MERROR);
// 			free(tmp);
// 		}
// 		redir = cmd->redir;
// 		while (redir)
// 		{
// 			if (redir->token == D_LOWER)
// 			{
// 				if (checkifquotes(redir->next->word))
// 					redir->quotelim = true;
// 				tmp = trimquotes(redir->next->word);
// 				if (!tmp)
// 					exitmsg(shell, MERROR);
// 				free(redir->next->word);
// 				redir->next->word = ft_strdup(tmp);
// 				if (!redir->next->word)
// 					(free(tmp), exitmsg(shell, MERROR));
// 				free(tmp);
// 				redir = redir->next;
// 			}
// 			else
// 			{
// 				tmp = trimquotes(redir->word);
// 				if (!tmp)
// 					exitmsg(shell, MERROR);
// 				free(redir->word);
// 				redir->word = ft_strdup(tmp);
// 				if (!redir->word)
// 					(free(tmp), exitmsg(shell, MERROR));
// 				free(tmp);
// 				redir = redir->next;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// }
