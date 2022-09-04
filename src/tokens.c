/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:40:32 by mokoucha          #+#    #+#             */
/*   Updated: 2022/09/04 19:40:37 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_init(t_data *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error(NULL);
	token->next = NULL;
	token->type = NONE;
	token->tok = NULL;
	token->data = data;
	token->linker = 0;
	return (token);
}

static void	quotes(t_token **token, char *cmd_line, int *i)
{
	int		j;
	char	c;
	int		tmp;

	j = *i + 1;
	tmp = *i + 1;
	c = cmd_line[*i];
	if (handl_singl_things(i, cmd_line, tmp, c))
		return ;
	check_if_token_full(token);
	while (cmd_line[++*i])
	{
		if (cmd_line[*i] == c)
		{
			(*token)->tok = ft_substr(cmd_line, j, *i - j);
			if (c == '\"')
				(*token)->type = DOUBLE_QUOTE;
			else if (c == '\'')
				(*token)->type = SINGLE_QUOTE;
			if (!is_here(cmd_line[*i + 1], " \t\n\v\f\r><"))
				(*token)->linker = 1;
			break ;
		}
	}
}

static void	redirecters(t_token **token, char *cmd_line, int *i)
{
	check_if_token_full(token);
	if (cmd_line[*i] == '<' && cmd_line[*i + 1] == '<')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 2);
		(*i)++;
		(*token)->type = HERE_DOC;
	}
	else if (cmd_line[*i] == '<')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 1);
		(*token)->type = REDIRECT_IN;
	}
	else if (cmd_line[*i] == '>' && cmd_line[*i + 1] == '>')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 2);
		(*i)++;
		(*token)->type = REDIRECT_OUT_APP;
	}
	else if (cmd_line[*i] == '>')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 1);
		(*token)->type = REDIRECT_OUT;
	}
}

static void	words(t_token **token, char *cmd_line, int *i)
{
	int	j;

	j = *i;
	if (!cmd_line[*i])
		return ;
	check_if_token_full(token);
	while (!is_here(cmd_line[*i], " <>\'\"") && cmd_line[*i])
		(*i)++;
	if (is_here(cmd_line[*i], "\'\""))
		(*token)->linker = 1;
	(*i)--;
	(*token)->tok = ft_substr(cmd_line, j, (*i - j) + 1);
	(*token)->type = WORD;
}

int	get_tokens(char *all_cmd, t_mini_data *mini_cmd)
{
	t_token	*token;
	int		i;
	int		j;

	i = -1;
	j = 0;
	mini_cmd->token_list = token_init(mini_cmd->data);
	mini_cmd->token_list->last_type = NONE;
	token = mini_cmd->token_list;
	while (all_cmd[++i])
	{
		if (is_here(all_cmd[i], "\"\'"))
			quotes(&token, all_cmd, &i);
		else if (is_here(all_cmd[i], "<>"))
			redirecters(&token, all_cmd, &i);
		else if (!is_here(all_cmd[i], " \t\n\v\f\r"))
			words(&token, all_cmd, &i);
	}
	if (update_my_tokens(mini_cmd))
		return (1);
	return (0);
}
