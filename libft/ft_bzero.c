/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:37:46 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:43:16 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t size)
{
	size_t	loop;

	loop = 0;
	while (loop < size)
	{
		((unsigned char *)dest)[loop] = 0;
		loop++;
	}
	return (dest);
}
