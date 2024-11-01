/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/10/31 10:37:34 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_type(t_token *united)
{
	while (united)
	{
		if (united->prev == NULL || united->prev->type == PIPE)
			united->type = CMD;
		if (united->prev != NULL && (united->prev->type == RED_IN
			|| united->prev->type == RED_OUT || united->prev->type == APPEND))
			united->type = FILENAME;
		if (united->prev != NULL && (united->prev->type == HEREDOC))
			united->type = ENDKEY;
		united = united->next;
	}
}		
void del(void *content) {
    free(content);
}


t_token	*all_together(t_token **token_list)
{
	t_token	*united;
	t_token	*curr;

	united = *token_list;
	change_type(united);
	while (united)
	{
		if (united->type == CMD)
		{
			curr = united;
			while (curr != NULL && curr->type != PIPE)
			{
				if ((curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 1)
					united->content = ft_strjoin(united->content,
							curr->content);
				if (curr->prev && (curr->prev->type == S_QUOTES || curr->prev->type == D_QUOTES || curr->prev->type == CMD) && curr->prev->quote_issue == 2)
					united->content = ft_strjoin(united->content,
							curr->content);
				else if ((curr->type == WORD || curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 0)
				{
					united->content = ft_strjoin(united->content, " ");
					united->content = ft_strjoin(united->content,
							curr->content);
					// curr->next = NULL;
					// curr->prev = NULL;
					//curr->next->prev = curr->prev;
				}
				curr = curr->next;
			}
		}
		united = united->next;
	}
	return (united);
}

t_token	*clear_list(t_token **token_list)
{
	t_token	*united;
	t_token	*temp;

	united = *token_list;
	while (united)
	{
		temp = united->next;
		if (united->type == WORD || united->type == S_QUOTES || united->type == D_QUOTES)
		{
			if (united->prev != NULL)
				united->prev->next = united->next;
			if (united->next != NULL)
				united->next->prev = united->prev;
			free(united);
		}
		united = temp;
	}
	return (united);
}
