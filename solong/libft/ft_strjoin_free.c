/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 01:01:55 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:57:44 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_len_set(char *s)
{
	int	len;

	if (s == NULL)
		len = 0;
	else
		len = ft_strlen(s);
	return (len);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
	size_t	loop;

	if (s1 == 0 && s2 == 0)
		return (0);
	s1_len = str_len_set(s1);
	s2_len = str_len_set(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == 0)
		return (0);
	loop = 0;
	while (loop < s1_len + s2_len + 1)
		str[loop++] = 0;
	ft_strlcat(str, s1, s1_len + 1);
	ft_strlcat(str, s2, s1_len + s2_len + 1);
	free(s1);
	free(s2);
	return (str);
}
