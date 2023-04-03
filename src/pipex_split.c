/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:12:58 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/03 13:48:48 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int		pipex_splitcount(char const *s, char c);
void			ft_free_split(char **arr);
static char		**pipex_fill_arr(char const *s, char c, char	**res, int cnt);

char	**pipex_split(char *s, char c)
{
	int		cnt;
	char	**res;
	int		i;

	if (!s)
		return (0);
	cnt = pipex_splitcount(s, c);
	res = malloc((cnt + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[cnt] = 0;
	res = pipex_fill_arr(s, c, res, cnt);
	i = 0;
	while (res[i])
	{
		res[i] = ft_strtrim(res[i], "'");
		i++;
	}
	return (res);
}

static char	**pipex_fill_arr(char const *s, char c, char **res, int cnt)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (s[i] && j < cnt)
	{
		i = skip_quotes(s, i);
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			start = i;
		i = skip_quotes(s, i);
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			res[j] = ft_substr(s, start, (i - start));
			if (!res[j])
				return (ft_free_split(res), NULL);
			j++;
		}
	}
	return (res);
}

static int	pipex_splitcount(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			cnt++;
		if (*s == '\'')
		{
			s++;
			while (*s != '\'' && *s != '\0')
				s++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	return (cnt);
}

int	skip_quotes(char const *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
			i++;
	}
	return (i);
}
