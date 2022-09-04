/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:44:36 by rdoukali          #+#    #+#             */
/*   Updated: 2022/09/04 20:30:55 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	grep_pwd(char *s)
{
	int	i;

	i = -1;
	while (g_data.my_env[++i])
		if (!ft_strncmp(g_data.my_env[i], s, ft_strlen(s)))
			return (i);
	return (-1);
}

void	add_new_pwd(char *old)
{
	char	**temp_env;

	temp_env = ft_calloc ((g_data.count + 2), sizeof(char *));
	if (!temp_env)
		ft_error(NULL);
	g_data.count = -1;
	while (g_data.my_env[++g_data.count])
		temp_env[g_data.count] = ft_strdup (g_data.my_env[g_data.count]);
	temp_env[g_data.count++] = ft_strjoin ("OLDPWD=", old);
	temp_env[g_data.count] = 0;
	ft_free (g_data.my_env);
	g_data.my_env = temp_env;
	g_data.first_pwd = 1;
}

void	ft_setpwd(char *old)
{
	int			i;
	char		*new;

	new = getcwd (NULL, 0);
	i = grep_pwd("PWD=");
	if (i != -1)
	{
		free (g_data.my_env[i]);
		g_data.my_env[i] = ft_strjoin ("PWD=", new);
	}
	free(new);
	i = grep_pwd("OLDPWD=");
	if (g_data.first_pwd == 0 && i == -1)
		add_new_pwd(old);
	else
	{
		free (g_data.my_env[i]);
		g_data.my_env[i] = ft_strjoin("OLDPWD=", old);
	}
	free (old);
}

void	cd_error(char *str)
{
	g_data.errsv = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	ft_cd(t_mini_data *mini_data)
{
	t_token	*head;
	char	*old;

	g_data.errsv = 0;
	old = getcwd(NULL, 0);
	head = grep_a_type(mini_data->token_list, CMD);
	while (head->next && head->next->type != ARGS)
		head = head->next;
	if (head->next && head->next->type == ARGS)
	{
		if (!head->next->tok[0])
			ft_setpwd (old);
		else if (chdir(head->next->tok))
		{
			free(old);
			cd_error(head->next->tok);
		}
		else
			ft_setpwd(old);
		return ;
	}
	ft_cd_2(old);
}
