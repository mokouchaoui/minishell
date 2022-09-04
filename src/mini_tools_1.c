/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:37:23 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:37:24 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_full_path(char *to_find)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(to_find, "=");
	len = ft_strlen(tmp);
	while (g_data.my_env[++i])
	{
		if (!ft_strncmp(g_data.my_env[i], tmp, len))
		{
			free(tmp);
			return (g_data.my_env[i] + len);
		}
	}
	free(tmp);
	return (NULL);
}

int	if_just_spaces(char *str)
{
	while (*str)
	{
		if (!is_here(*str, " \t\n\v\f\r"))
			break ;
		str++;
	}
	if (!*str)
		return (1);
	else
		return (0);
}

int	is_here(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	check_if_token_full(t_token **token)
{
	if ((*token)->type != NONE)
	{
		(*token)->next = token_init((*token)->data);
		(*token)->next->last_type = (*token)->type;
		(*token) = (*token)->next;
	}
}

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_data.errsv = 1;
}
