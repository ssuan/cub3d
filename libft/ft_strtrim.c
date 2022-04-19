/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:40 by daelee            #+#    #+#             */
/*   Updated: 2021/11/25 17:48:30 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_front(const char *s1, const char *set)
{
	size_t	len;
	size_t	loop;

	len = ft_strlen(s1);
	loop = 0;
	while (loop < len)
	{
		if (ft_strchr(set, s1[loop]) == 0)
			break ;
		loop++;
	}
	return (loop);
}

int	find_end(const char *s1, const char *set)
{
	size_t	len;
	size_t	loop;

	len = ft_strlen(s1);
	loop = 0;
	while (loop < len)
	{
		if (ft_strchr(set, s1[len - loop - 1]) == 0)
			break ;
		loop++;
	}
	return (len - loop);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front;
	int		end;
	char	*str;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	front = find_front(s1, set);
	end = find_end(s1, set);
	if (front >= end)
		return (ft_strdup(""));
	str = (char *)ft_calloc(sizeof(char), (end - front + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1 + front, end - front + 1);
	return (str);
}
