/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:17:30 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:44:27 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_value(char *temp_str, char *str, int len, int sign)
{
	int	loop;

	loop = 0;
	if (sign == 1)
		str[loop++] = '-';
	while (len > 0)
		str[loop++] = temp_str[len-- - 1];
}

char	*ft_itoa(int n)
{
	char	temp_str[20];
	char	*str;
	int		sign;
	int		len;

	sign = 0;
	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	while (n >= 10)
	{
		temp_str[len++] = '0' + (n % 10);
		n = n / 10;
	}
	temp_str[len++] = '0' + n % 10;
	str = ft_calloc(sizeof(char), len + sign + 1);
	if (str == 0)
		return (0);
	set_value(temp_str, str, len, sign);
	return (str);
}
