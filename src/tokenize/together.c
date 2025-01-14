/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 17:05:32 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_cmd_args(t_token *united)
{
	int		i;
	t_token	*temp;

	i = 1;
	temp = united;
	while (temp && temp->type != PIPE)
	{
		i++;
		temp = temp->next;
	}
	united->cmd_args = (char **)malloc(sizeof(char *) * i + 1);
}

void	change_type(t_token *united)
{
	t_token	*temp;
	int		i;

	i = 0;
	assign_initial_types(united);
	temp = united;
	while (temp)
	{
		if (temp->type == CMD)
			i++;
		temp = temp->next;
	}
	if (i == 0)
	{
		temp = united;
		while (temp)
		{
			if (temp->type == WORD)
			{
				temp->type = CMD;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	assign_initial_types(t_token *united)
{
	t_token	*temp;

	temp = united;
	while (temp)
	{
		if ((temp->prev == NULL || temp->prev->type == PIPE)
			&& is_redirect(temp->type) == 0)
		{
			temp->type = CMD;
			malloc_cmd_args(temp);
		}
		if (temp->prev != NULL && (temp->prev->type == RED_IN
				|| temp->prev->type == RED_OUT || temp->prev->type == APPEND))
			temp->type = FILENAME;
		temp = temp->next;
	}
}

t_token	*clear_list(t_token **token_list)
{
	t_token	*united;
	t_token	*temp;

	united = *token_list;
	while (united)
	{
		temp = united->next;
		if (united->type == WORD || united->type == S_QUOTES
			|| united->type == D_QUOTES)
		{
			if (united->prev != NULL)
				united->prev->next = united->next;
			if (united->next != NULL)
				united->next->prev = united->prev;
			free(united->content);
			free(united);
			united = NULL;
		}
		united = temp;
	}
	return (united);
}
