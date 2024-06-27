/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:30:15 by yabejani          #+#    #+#             */
/*   Updated: 2024/01/22 14:43:49 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *save)
{
	char	*tmp;
	int		readbytes;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	readbytes = 1;
	if (!save)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	while (!ft_strchrgnl(save, '\n') && readbytes != 0)
	{
		readbytes = read(fd, tmp, BUFFER_SIZE);
		if (readbytes == -1)
			return (free(tmp), free(save), NULL);
		tmp[readbytes] = '\0';
		if (readbytes == 0)
			break ;
		save = ft_strjoinfree(save, tmp);
	}
	return (free(tmp), save);
}

char	*ft_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
	{
		line = ft_strndup(save, i + 1);
		i++;
	}
	else
		line = ft_strndup(save, i);
	return (line);
}

char	*ft_clean_save(char *save)
{
	int		i;
	int		len;
	char	*newsave;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	len = ft_strlengnl(save);
	if (!save[i])
		return (free(save), NULL);
	newsave = ft_strndup((save + i + 1), (len - i));
	if (newsave)
		free(save);
	return (newsave);
}

char	*ft_get_next_line(int fd)
{
	static char	*save[4096];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd] || !save[fd][0])
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(save[fd]);
	if (!line || line[0] == 0)
		return (free(line), free(save[fd]), NULL);
	save[fd] = ft_clean_save(save[fd]);
	if (save[fd] && save[fd][0] == '\0')
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (line);
}
