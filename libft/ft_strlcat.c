/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:27:05 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:47:22 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	loop;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	loop = 0;
	if (dest_len > size - 1 || size == 0)
		return (size + src_len);
	if (dest_len < size - 1)
	{
		while (src[loop] != 0 && dest_len + loop < size - 1)
		{
			dest[dest_len + loop] = src[loop];
			loop++;
		}
	}
	dest[dest_len + loop] = 0;
	return (dest_len + src_len);
}
