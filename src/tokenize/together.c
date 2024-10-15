/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/10/15 12:17:14 by anacaro5         ###   ########.fr       */
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
				if (curr->type == WORD)
				{
					united->content = ft_strjoin(united->content, " ");
					united->content = ft_strjoin(united->content,
							curr->content);
				}
				curr = curr->next;
			}
		}
		united = united->next;
	}
	return (united);
}
