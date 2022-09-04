/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:27:35 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:55:10 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str2;

	i = 0;
	str2 = b;
	while (i < len)
	{
		str2[i] = (char)c;
		i++;
	}
	return (str2);
}
