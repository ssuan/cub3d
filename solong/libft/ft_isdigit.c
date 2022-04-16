/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:43:06 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:44:14 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	unsigned char	check;

	if (c >= 256 || c < 0)
		return (0);
	check = (unsigned char)c;
	if (check >= '0' && check <= '9')
		return (1);
	else
		return (0);
}
