/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:54:32 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:48:08 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *dest, int check)
{
	char			*save_point;
	unsigned char	check_char;

	save_point = 0;
	check_char = (unsigned char)check;
	while (1)
	{
		if (*dest == (char)check)
			save_point = (char *)dest;
		if (*dest == 0)
			return (save_point);
		dest++;
	}
	return (0);
}
