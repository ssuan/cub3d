/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:16:30 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:50:20 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *dest, const char *src, size_t size)
{
	size_t			loop;
	unsigned char	*dest_copy;
	unsigned char	*src_copy;

	dest_copy = (unsigned char *)dest;
	src_copy = (unsigned char *)src;
	loop = 0;
	while (loop < size)
	{
		if (dest_copy[loop] != src_copy[loop]
			|| dest_copy[loop] == 0 || src_copy[loop] == 0)
			return ((int)(dest_copy[loop] - src_copy[loop]));
		loop++;
	}
	return (0);
}
