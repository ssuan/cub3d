/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:32:13 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:28 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_value_fd(char *temp_str, char *str, int len, int sign)
{
	int	loop;

	loop = 0;
	if (sign == 1)
		str[loop++] = '-';
	while (len > 0)
		str[loop++] = temp_str[len-- - 1];
}

void	ft_itoa_fd(int n, int fd)
{
	char	temp_str[20];
	char	new_str[20];
	int		sign;
	int		len;

	sign = 0;
	len = 0;
	ft_bzero(temp_str, 20);
	ft_bzero(new_str, 20);
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
	set_value_fd(temp_str, new_str, len, sign);
	write(fd, new_str, ft_strlen(new_str));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	ft_itoa_fd(n, fd);
}
