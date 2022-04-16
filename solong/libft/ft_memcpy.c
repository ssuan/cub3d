/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:32:08 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:04 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	loop;

	if (dest == 0 && src == 0)
		return (0);
	loop = 0;
	while (loop < size)
	{
		((unsigned char *)dest)[loop] = ((unsigned char *)src)[loop];
		loop++;
	}
	return (dest);
}
