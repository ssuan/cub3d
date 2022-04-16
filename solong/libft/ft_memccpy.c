/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:28:35 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:45:44 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int check, size_t size)
{
	size_t	loop;

	loop = 0;
	while (loop < size)
	{
		((unsigned char *)dest)[loop] = ((unsigned char *)src)[loop];
		if (((unsigned char *)src)[loop] == (unsigned char)check)
			return (&((unsigned char *)dest)[loop + 1]);
		loop++;
	}
	return (0);
}
