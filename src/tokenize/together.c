/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 16:06:54 by jbolanho         ###   ########.fr       */
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

// t_token	*all_together(t_token **token_list)
// {
// 	t_token	*united;
// 	t_token	*curr;
// 	t_token	*temp;
// 	int		i;

// 	i = 0;
// 	united = *token_list;
// 	change_type(united);
// 	while (united)
// 	{
// 		if (united->type == CMD)
// 		{
// 			i = 0;
// 			curr = united;
// 			if (curr->content == NULL)
// 			{
// 				curr = curr->next;
// 			}
// 			while (curr != NULL && curr->type != PIPE)
// 			{
// 				if (curr->next && curr->next->quote_issue_prev == 1
// 					&& is_redirect(curr->type) != 1 && curr->type != FILENAME)
// 				{
// 					united->cmd_args[i] =
// 						ft_strjoin(curr->content, curr->next->content);
// 					curr = curr->next;
// 				}
// 				if (curr->next && curr->quote_issue_next == 1
// 					&& is_redirect(curr->type) != 1 && curr->type != FILENAME)
// 				{
// 					if (united->cmd_args[i])
// 					{
// 						united->cmd_args[i] =
// 							ft_strjoin(united->cmd_args[i],
//								curr->next->content);
// 						curr = curr->next;
// 					}
// 					else
// 					{
// 						united->cmd_args[i] =
// 							ft_strjoin(curr->content, curr->next->content);
// 						curr = curr->next;
// 					}
// 				}
// 				else if (is_redirect(curr->type) != 1 && curr->type != FILENAME
// 					&& curr->quote_issue_prev == 0 
// 					&& curr->quote_issue_next == 0)
// 				{
// 					united->cmd_args[i] = ft_strdup(curr->content);
// 				}
// 				else if (is_redirect(curr->type) == 1 || curr->type == FILENAME)
// 					i--;
// 				curr = curr->next;
// 				i++;
// 			}
// 			united->cmd_args[i] = NULL;
// 		}
// 		united = united->next;
// 	}
// 	i = 0;
// 	temp = *token_list;
// 	while (temp)
// 	{
// 		if (temp->cmd_args != NULL)
// 			while (temp->cmd_args[i])
// 				i++;
// 		temp = temp->next;
// 	}
// 	return (united);
// }
