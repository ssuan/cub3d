/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:36:08 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:18 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int fill_char, size_t size)
{
	size_t	loop;

	loop = 0;
	while (loop < size)
	{
		((unsigned char *)dest)[loop] = (unsigned char)fill_char;
		loop++;
	}
	return (dest);
}
