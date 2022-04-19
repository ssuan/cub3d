/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 23:06:07 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:48:03 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	int		size;

	i = 0;
	j = 0;
	if (*src == '\0')
		return ((char *)dest);
	if ((src == NULL && dest == NULL) || len == 0)
		return (NULL);
	size = ft_strlen(src);
	while (i < len && dest[j])
	{
		if (i + size > len)
			return (NULL);
		if (ft_strncmp(dest + j, src, size) == 0)
			return ((char *)dest + i);
		i++;
		j++;
	}
	return (NULL);
}
