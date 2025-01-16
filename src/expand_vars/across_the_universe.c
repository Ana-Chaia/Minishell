/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   across_the_universe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:39 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/16 17:06:58 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	across_the_universe(t_token **token_list)
{
	t_token	*temp;
	char	*curr;
	char	*new_content;

	temp = *token_list;
	while (temp)
	{
		if (temp->type == D_QUOTES || temp->type == S_QUOTES)
		{
			curr = ft_substr(temp->content, 1, (ft_strlen(temp->content) - 2));
			free (temp->content);
			temp->content = curr;
		}
		if (temp->type == D_QUOTES || temp->type == WORD)
		{
			new_content = find_dollar(temp->content);
			free(temp->content);
			temp->content = new_content;
		}
		temp = temp->next;
	}
}

char	*find_dollar(char *cmd)
{
	int		i;
	int		start;
	char	*new;
	char	*temp;

	i = 0;
	new = NULL;
	while (cmd[i] != '\0')
	{
		start = i;
		while (cmd[i] != '\0' && cmd[i] != '$')
			i++;
		if (i > start)
		{
			temp = ft_substr(cmd, start, i - start);
			new = ft_strjoin(new, temp);
			free(temp);
		}
		if (cmd[i] == '$')
			new = handle_dollar (cmd, &i, new);
	}
	return (new);
}

char	*handle_dollar(char *cmd, int *i, char *new)
{
	char	*value;
	char	*temp;

	value = NULL;
	temp = NULL;
	(*i)++;
	if (validate_name (&cmd[*i]) != 1 && cmd[*i] != '?')
		value = ft_strdup("$");
	else if (cmd[*i] == '?')
	{
		value = ft_itoa(get_status(-1));
		(*i)++;
	}
	else
		value = handle_variable(cmd, i, &temp);
	if (value)
		new = append_to_new(new, value);
	if (temp)
		new = append_to_new(new, temp);
	return (new);
}

char	*append_to_new(char *new, char *name)
{
	char	*new1;

	new1 = new;
	new = ft_strjoin(new1, name);
	free(new1);
	free(name);
	return (new);
}

char	*handle_variable(char *cmd, int *i, char **temp)
{
	char	*value;
	int		start;
	int		j;

	start = *i - 1;
	while (cmd[*i] != '\0' && cmd[*i] != ' ' && cmd[*i] != '$'
		&& cmd[*i] != '\'' && cmd[*i] != '"')
		(*i)++;
	value = change_dollar(cmd, start, *i - 1);
	if (cmd[*i] == '\'' || cmd[*i] == '"')
	{
		j = *i;
		while (cmd[*i] != '\0' && cmd[*i] != ' ' && cmd[*i] != '$')
			(*i)++;
		*temp = ft_substr(cmd, j, *i);
	}
	return (value);
}
