/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/10/14 12:15:57 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_type(t_token *united)
{
	while (united)
	{
		if (united->prev == NULL || united->prev->type == PIPE)
			united->type = CMD;
		if (united->prev == RED_IN || united->prev == RED_OUT
			|| united->prev == APPEND)
			united->type = FILENAME;
		if (united->prev == HEREDOC)
			united->type = ENDKEY;
		united = united->next;
	}
}		

t_token	all_together(t_token **token_list)
{
	t_token	*united;

	united = *token_list;
	change_type(united);
	if (united->type == CMD)
	{
		while (united->next->type != PIPE || united->next != NULL)
		{ 
			if (united->content == WORD)
			{
				united->content = ft_strjoin(united->content,
						united->next->content);
			}
			united = united->next;
		}
	}
		
	}
}