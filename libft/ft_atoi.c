/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:31:00 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:53:47 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_isspace(char e)
{
	return (e == ' ' || e == '\f' || e == '\r' || e == '\v'
		|| e == '\t' || e == '\n');
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nb;
	int		index;

		index = 0;
		nb = 0;
		sign = 1;
	while (ft_isspace(str[index]))
			index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
				sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		nb = nb * 10 + (str[index] - '0');
		if (nb > 2147483647 && sign == 1)
			return (-1);
		if (nb > 2147483648 && sign == -1)
			return (0);
		index++;
	}
	return (sign * nb);
}
