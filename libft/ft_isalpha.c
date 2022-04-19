/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:37:48 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:43:59 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	check;

	if (c >= 256 || c < 0)
		return (0);
	check = (unsigned char)c;
	if ((check >= 'a' && check <= 'z')
		|| (check >= 'A' && check <= 'Z'))
		return (1);
	else
		return (0);
}
