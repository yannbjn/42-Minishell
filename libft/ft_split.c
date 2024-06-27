/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:41:34 by yabejani          #+#    #+#             */
/*   Updated: 2024/06/11 19:26:15 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	word_count(char const *s, char c)
{
	size_t	wc;
	size_t	i;

	wc = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wc++;
		i++;
	}
	return (wc);
}

static void	fill_array(char *new, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static char	**mem_set(char **tab, char const *s, char c)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && s[index + count] != c)
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return (free_tab(tab), NULL);
			fill_array(tab[i], (s + index), c);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab = mem_set(tab, s, c);
	if (!tab)
		return (NULL);
	return (tab);
}

// static int	ft_iss_sep(char d, char c)
// {
// 	if (d == c)
// 		return (1);
// 	if (d == '\0')
// 		return (1);
// 	return (0);
// }

// static int	ft_count_strings(char const *str, char c)
// {
// 	int	i;
// 	int	strings;

// 	strings = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_iss_sep(str[i + 1], c) == 1 && ft_iss_sep(str[i], c) == 0)
// 			strings++;
// 		i++;
// 	}
// 	return (strings);
// }

// static void	ft_strrcpy(char *dest, char const *src, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_iss_sep(src[i], c) == 0)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// }

// static int	ft_split_strings(char **ptr, char const *str, char c)
// {
// 	int	i;
// 	int	j;
// 	int	string;

// 	string = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_iss_sep(str[i], c) == 1)
// 			i++;
// 		else
// 		{
// 			j = 0;
// 			while (ft_iss_sep(str[i + j], c) == 0)
// 				j++;
// 			ptr[string] = (char *)malloc(sizeof(char) * (j + 1));
// 			if (!ptr[string])
// 				return (0);
// 			ft_strrcpy(ptr[string], str + i, c);
// 			i += j;
// 			string++;
// 		}
// 	}
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ptr;
// 	int		totstrings;

// 	if (!s)
// 		return (NULL);
// 	totstrings = ft_count_strings(s, c);
// 	ptr = malloc(sizeof(char *) * (totstrings + 1));
// 	if (!ptr)
// 		return (NULL);
// 	ptr[totstrings] = 0;
// 	if (ft_split_strings(ptr, s, c) == 0)
// 		return (free_tab(ptr), NULL);
// 	return (ptr);
// }
