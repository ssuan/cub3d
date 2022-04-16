/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:12:58 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:42:38 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(char *msg)
{
	printf("\e[31m\e[1mError\n%s \e[0m \n", msg);
	exit (EXIT_FAILURE);
	return (FAILURE);
}
