/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:38:44 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:38:46 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_arry(int **arry, int len)
{
	int	i;

	i = 0;
	if (arry)
	{
		while (i < len)
		{
			free(arry[i]);
			i++;
		}
		free(arry);
	}
}

void	free_all(t_data *data, int **pipes, int count)
{
	int		i;
	t_token	*tmp;
	t_token	*token;

	i = 0;
	free_2d_arry(pipes, count);
	while (i < data->num_cmds)
	{
		token = data->mini_cmds[i].token_list;
		free(data->mini_cmds[i].all_cmd);
		while (token)
		{
			tmp = token->next;
			free(token->tok);
			free(token);
			token = tmp;
		}
		i++;
	}
	free(data->mini_cmds);
	free(data->cmd_line);
}

t_token	*grep_a_type(t_token *token, int type)
{
	while (token)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	if_builtins_cmds(t_mini_data *mini_data)
{
	t_token	*token;

	token = grep_a_type(mini_data->token_list, CMD);
	if (!token)
		return (1);
	if (!ft_strcmp(token->tok, "echo"))
		return (0);
	else if (!ft_strcmp(token->tok, "pwd"))
		return (0);
	else if (!ft_strcmp(token->tok, "cd"))
		return (0);
	else if (!ft_strcmp(token->tok, "env"))
		return (0);
	else if (!ft_strcmp(token->tok, "export"))
		return (0);
	else if (!ft_strcmp(token->tok, "unset"))
		return (0);
	else if (!ft_strcmp(token->tok, "exit"))
		return (0);
	return (1);
}

void	execute_builtins_cmds(t_mini_data *mini_data)
{
	t_token	*token;

	token = grep_a_type(mini_data->token_list, CMD);
	if (!token)
		return ;
	if (!ft_strcmp(token->tok, "echo"))
		ft_echo(mini_data);
	else if (!ft_strcmp(token->tok, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(token->tok, "cd"))
		ft_cd(mini_data);
	else if (!ft_strcmp(token->tok, "env"))
		ft_env();
	else if (!ft_strcmp(token->tok, "export"))
		ft_export(mini_data);
	else if (!ft_strcmp(token->tok, "unset"))
		ft_unset(mini_data);
	else if (!ft_strcmp(token->tok, "exit"))
		ft_exit(mini_data);
}
