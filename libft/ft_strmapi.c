/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:32:24 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:56:05 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = (f(i, s[i]));
		i++;
	}
	res[i] = '\0';
	return (res);
}
