/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:40:03 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:40:05 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	*open_files(t_mini_data *mini_data)
{
	int		num_fd;
	int		*fd;
	t_token	*token;
	int		i;

	num_fd = number_of_types(mini_data, OUT_FILE);
	num_fd += number_of_types(mini_data, IN_FILE);
	num_fd += number_of_types(mini_data, OUT_FILE_APP);
	if (num_fd == 0)
		return (NULL);
	fd = malloc(sizeof(int) * (num_fd + 1));
	if (!fd)
		ft_error(NULL);
	fd[num_fd] = -1;
	token = mini_data->token_list;
	i = 0;
	while (token)
	{
		creat_files(token, fd, &i);
		token = token->next;
	}
	return (fd);
}

void	init_to_start(t_data *data, int	***pipes, int *num_pipes, int *l_type)
{
	*num_pipes = get_pipes(data, pipes);
	*l_type = LASTONE;
	data->pid = malloc(sizeof(int) * data->num_cmds);
	if (!data->pid)
		ft_error(NULL);
}

void	mix_tokens(t_token **token)
{
	char	*tmp;
	t_token	*tmp_token;

	tmp_token = (*token)->next->next;
	tmp = (*token)->tok;
	(*token)->tok = ft_strjoin((*token)->tok, (*token)->next->tok);
	free(tmp);
	free((*token)->next->tok);
	free((*token)->next);
	(*token)->next = tmp_token;
}

void	combine_the_words(t_token *token)
{
	while (token)
	{
		if (token->linker && token->next)
		{
			while (token->next && token->next->linker)
				mix_tokens(&token);
			if (token->next)
				mix_tokens(&token);
			token->linker = 0;
		}
		else
			token = token->next;
	}
}
