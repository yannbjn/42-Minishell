/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:21 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/27 15:34:23 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_sig = 0;

static char	*get_dir(void)
{
	char	*buffer;
	char	*str;

	buffer = ft_calloc(PATH_MAX, sizeof(char *));
	buffer = getcwd(buffer, PATH_MAX);
	str = ft_strjoin(buffer, "> ");
	free(buffer);
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	shell;

	if (ac != 1 && av)
		exitmsg(&shell, ERRARG);
	initinitinit(&shell);
	init_shell(&shell, envp);
	ft_signals();
	while (1 != 2 && 2147483647 > -2147483648)
	{
		shell.cwd = get_dir();
		line = readline(shell.cwd);
		if (!line)
			break ;
		catchsignals(&shell);
		add_history(line);
		lexer(&shell, line);
		if (shell.lex && shell.excode != 2)
			(parser(&shell), launch_exec(&shell));
		resetloop(&shell);
		if (line)
			free(line);
	}
	ft_freeshell(&shell);
	(fd_printf(1, "exit\n"), exit(shell.excode));
}
// stocker tmp excode ou excode et si !0 ecrire dans error output
// verifier ou ecrire le exit
// free input PITIE PENSER A FREE INPUT DANS WHILE (1)

// node = shell.cmd;
// int	i;
// while (node)
// {
// 	if (node->tab)
// 	{
// 		i = 0;
// 		while (node->tab[i])
// 			printf("%s\n", node->tab[i++]);
// 	}
// 	node = node->next;
// }

// while (lex)
// {
// 	printf("%s\n", lex->word);
// 	lex = lex->next;
// }
