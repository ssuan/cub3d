/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:08:58 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:47:26 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	src_size;

	if (dest == 0 || src == 0)
		return (0);
	src_size = ft_strlen(src);
	if (dest_size == 0)
		return (src_size);
	else if (src_size < dest_size)
	{
		ft_memcpy(dest, src, src_size);
		dest[src_size] = 0;
	}
	else
	{
		ft_memcpy(dest, src, dest_size - 1);
		dest[dest_size - 1] = 0;
	}
	return (src_size);
}
