/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:31:29 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:50:42 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *dest, const void *src, size_t size)
{
	unsigned char	*dest_char;
	unsigned char	*src_char;
	size_t			loop;

	loop = 0;
	dest_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	while (loop < size)
	{
		if (dest_char[loop] != src_char[loop])
			return (dest_char[loop] - src_char[loop]);
		loop++;
	}
	return (0);
}
