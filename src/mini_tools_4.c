/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:39:54 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:39:55 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_cmds)
	{
		if (check_syntax_errors(&data->mini_cmds[i]))
			return (1);
	}
	return (0);
}

void	set_hd_and_f(t_mini_data *mini_data, int *fd_files)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == HERE_DOC && mini_data->last_herdoc != -1)
		{
			if (dup2(mini_data->last_herdoc, STDIN_FILENO) == -1)
				ft_error(NULL);
		}
		else if (token->type == OUT_FILE || \
		token->type == IN_FILE || token->type == OUT_FILE_APP)
			dup_all_files(token, fd_files, &i);
		token = token->next;
	}
}

void	close_p(t_mini_data *mini_data, int **pipes, int last_type, int index)
{
	int	i;

	i = 0;
	if (mini_data->type == PIPE || last_type == PIPE)
	{
		while (i < g_data.num_cmds - 1)
		{
			if (mini_data->type == PIPE && i != index)
				close(pipes[i][WRITE]);
			else if (mini_data->type != PIPE)
				close(pipes[i][WRITE]);
			if (last_type == PIPE && i != index - 1)
				close(pipes[i][READ]);
			else if (last_type != PIPE)
				close(pipes[i][READ]);
			i++;
		}
	}
}

void	set_reder(t_mini_data *mini_data, int **pipes, int last_type, int index)
{
	close_p(mini_data, pipes, last_type, index);
	if (mini_data->type == PIPE)
	{
		if (dup2(pipes[index][WRITE], STDOUT_FILENO) == -1)
			ft_error(NULL);
	}
	if (last_type == PIPE)
	{
		if (dup2(pipes[index - 1][READ], STDIN_FILENO) == -1)
			ft_error(NULL);
	}
}

void	dup_all_files(t_token *token, int *fd, int *i)
{
	if (token->type == OUT_FILE)
	{
		if (dup2(fd[(*i)++], STDOUT_FILENO) == -1)
			ft_error(NULL);
	}
	else if (token->type == IN_FILE)
	{
		if (dup2(fd[(*i)++], STDIN_FILENO) == -1)
			ft_error(NULL);
	}
	else if (token->type == OUT_FILE_APP)
	{
		if (dup2(fd[(*i)++], STDOUT_FILENO) == -1)
			ft_error(NULL);
	}
}
