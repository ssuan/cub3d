/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:05:49 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:50:28 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *dest, const char *src)
{
	size_t	i;

	if (src[0] == '\0')
		return ((char *)dest);
	while (*dest != '\0')
	{
		i = 0;
		while (*(dest + i) == *(src + i))
		{
			i++;
			if (*(src + i) == '\0')
				return ((char *)dest);
		}
		dest++;
	}
	return (0);
}
