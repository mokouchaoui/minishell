/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:22:19 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:53:54 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;

	new = malloc(count * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, (count * size));
	return ((void *)new);
}
