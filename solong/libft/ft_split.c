/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:34:13 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:47 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**str_malloc_count(char *str, char check)
{
	char	**words;
	int		state;
	int		count;
	int		loop;

	state = 0;
	count = 0;
	loop = 0;
	while (str[loop] != 0)
	{
		if (str[loop] == check)
			state = 0;
		else
		{
			if (state == 0)
				count++;
			state = 1;
		}
		loop++;
	}
	words = (char **)ft_calloc(sizeof(char *), count + 1);
	return (words);
}

char	*str_rangecopy(char *str, char check, size_t start)
{
	char	*dest;
	size_t	len;
	size_t	loop;

	len = start;
	while (str[len] != check)
		len++;
	dest = (char *)ft_calloc(sizeof(char), (len - start + 1));
	if (dest == 0)
		return (0);
	loop = 0;
	while (loop + start < len)
	{
		dest[loop] = str[start + loop];
		loop++;
	}
	dest[loop] = 0;
	return (dest);
}

void	fill_words(char **words, char *str, char check)
{
	int		len;
	int		state;
	int		loop;

	len = -1;
	state = 0;
	loop = -1;
	while (str[++len] != 0)
	{
		if (str[len] == check)
			state = 0;
		else if (state == 0)
		{
			words[++loop] = str_rangecopy(str, check, len);
			state = 1;
		}
	}
	words[++loop] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (s == 0)
		return (0);
	words = str_malloc_count((char *)s, c);
	if (words == 0)
		return (0);
	fill_words(words, (char *)s, c);
	return (words);
}
