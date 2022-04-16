/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:53:00 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:54 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*memory;

	len = ft_strlen(s);
	memory = (char *)malloc(len + 1);
	if (memory == 0)
		return (0);
	ft_bzero((void *)memory, len + 1);
	ft_memcpy(memory, s, len);
	memory[len] = 0;
	return (memory);
}
