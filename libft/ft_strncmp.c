/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:12:02 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:57:26 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int len)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < len)
		i++;
	if (i != len)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}
