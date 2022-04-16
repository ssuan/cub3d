/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:47:21 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:44:18 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	unsigned char	check;

	if (c >= 256 || c < 0)
		return (0);
	check = (unsigned char)c;
	if (check >= ' ' && check <= '~')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
