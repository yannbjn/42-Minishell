/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:45:29 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 14:24:48 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_newline(char **tab, int *flag)
{
	int	n;
	int	i;

	n = 1;
	while (tab[n] && tab[n][0] == '-' && tab[n][1] == 'n')
	{
		i = 1;
		if (tab[n][0] == '-' && tab[n][1] == 'n')
		{
			while (tab[n][i] == 'n')
				i++;
			if (tab[n][i] != '\0')
				return (n);
		}
		*flag = 1;
		n++;
	}
	return (n);
}

void	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	flag;
	int	ext;

	flag = 0;
	i = check_newline(cmd->tab, &flag);
	if (cmd->tab[1])
	{
		while (cmd->tab[i])
		{
			if (cmd->tab[i] && !cmd->tab[i + 1])
				printf("%s", cmd->tab[i++]);
			else if (cmd->tab[i])
				printf("%s ", cmd->tab[i++]);
		}
	}
	if (!flag)
		printf("\n");
	ext = shell->excode;
	ft_freeshell(shell);
	exit(ext);
}
//a checker verifier le exit(ext)
//c'etait tmpexcode avant on a peut etre tout casse