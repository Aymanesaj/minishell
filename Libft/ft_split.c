/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:29:40 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/13 14:47:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char ch, char c)
{
	if (c != ' ' && ch == c)
		return (1);
	else if (c != ' ' && ch != c)
		return (0);
	return (ch == c || ch == ' ' || ch == '\t' || ch == '\n'
		|| ch == '\v' || ch == '\f' || ch == '\r');
}

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && is_sep(s[i], c))
		i++;
	while (s[i])
	{
		if (!is_sep(s[i], c) && (is_sep(s[i + 1], c) || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_getlen(char const *s, char c, int *start)
{
	int	i;

	i = *start;
	while (s[i] && is_sep(s[i], c))
		i++;
	*start = i;
	while (s[i] && !is_sep(s[i], c))
		i++;
	return (i);
}

char	**ft_allocate(char const *s, char c, char **ptr, int count)
{
	int	start;
	int	i;
	int	len;

	i = 0;
	start = 0;
	while (i < count)
	{
		len = ft_getlen(s, c, &start);
		ptr[i] = ft_substr(s, start, len - start);
		if (ptr[i] == NULL)
		{
			while (i > 0)
			{
				i--;
				free(ptr[i]);
			}
			free(ptr);
			return (NULL);
		}
		start = len;
		i++;
	}
	ptr[count] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countword(s, c);
	ptr = (char **)ft_malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = ft_allocate(s, c, ptr, count);
	return (ptr);
}
