/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:43:33 by sunbchoi          #+#    #+#             */
/*   Updated: 2020/12/30 13:38:27 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	size_t	len;
	void	*memory;

	len = nelem * elsize;
	memory = malloc(len);
	if (memory == 0)
		return (0);
	ft_bzero(memory, len);
	return (memory);
}
