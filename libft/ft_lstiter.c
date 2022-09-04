/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:24:16 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:54:35 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	if (!lst ||!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
