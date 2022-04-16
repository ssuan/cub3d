/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:41:15 by sunbchoi          #+#    #+#             */
/*   Updated: 2020/12/28 21:04:11 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *dest, int check)
{
	while (1)
	{
		if (*dest == (char)check)
			return ((char *)dest);
		if (*dest == 0)
			return (0);
		dest++;
	}
}
