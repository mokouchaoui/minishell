/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:38:42 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:55:07 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	count;
	char	*d;
	char	*s;

	count = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!d && !s)
		return (NULL);
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else
	{
		while (count < len)
		{
			d[count] = s[count];
			count++;
		}
	}
	return ((void *)dst);
}
