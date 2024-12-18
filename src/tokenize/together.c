/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/18 14:43:38 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_cmd_args(t_token *united)
{
	int	i;
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
	//t_token	**cmd_args;
	int		i;

	i = 0;
	temp = united;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	//united->cmd_args = (char **)malloc(sizeof(char *) *  i + 1);
	i = 0;
	temp = united;
	while (temp)
	{
		if ((temp->prev == NULL || temp->prev->type == PIPE)
			&& is_redirect(temp->type) == 0)
		{
			temp->type = CMD;
			malloc_cmd_args(temp);
			//united->cmd_args[0] = ft_strdup(temp->content);
		}
		if (temp->prev != NULL && (temp->prev->type == RED_IN
				|| temp->prev->type == RED_OUT || temp->prev->type == APPEND))
			temp->type = FILENAME;

		temp = temp->next;
	}
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

//void	del(void *content)
//{
//	free(content);
//}


t_token	*all_together(t_token **token_list)
{
	t_token	*united;
	t_token	*curr;
	//t_token	**cmd_args;
	t_token		*temp;
	int		i;

	i = 0;
	united = *token_list;
	change_type(united);
	while (united)
	{
		if (united->type == CMD)
		{
			i = 0;
			curr = united;
			//malloc_cmd_args(united);
			// printf("curr->content: %s\n", curr->content);
			if (curr->content == NULL)
			{
				// printf("curr->content: %s\n", curr->next->content);
				// // united->cmd_args[i] = ft_strdup(curr->next->content);
				// // i++;
				// printf("curr->content: %s\n", united->cmd_args[i]);
				curr = curr->next;
			}
			while (curr != NULL && curr->type != PIPE)
			{
				if (curr->next && curr->next->quote_issue_prev == 1 && is_redirect(curr->type) != 1 && curr->type != FILENAME)
				{
					united->cmd_args[i] = ft_strjoin(curr->content, curr->next->content);
					curr = curr->next;
					//printf("1cmd_arg[%d]: %s\n", i, united->cmd_args[i]);
				}
				if (curr->next && curr->quote_issue_next == 1 && is_redirect(curr->type) != 1 && curr->type != FILENAME)
				{
					if (united->cmd_args[i])
					{
						//printf("2.1cmd_arg[%d]: %s\n", i, united->cmd_args[i]);
						united->cmd_args[i] = ft_strjoin(united->cmd_args[i], curr->next->content);
						//printf("2.2cmd_arg[%d]: %s\n", i, united->cmd_args[i]);
						curr = curr->next;
					}
					else
					{
						united->cmd_args[i] = ft_strjoin(curr->content, curr->next->content);
						//printf("3cmd_arg[%d]: %s\n", i, united->cmd_args[i]);
						curr = curr->next;
					}
				}
				else if (is_redirect(curr->type) != 1 && curr->type != FILENAME && curr->quote_issue_prev == 0 && curr->quote_issue_next == 0)
				{
					united->cmd_args[i] = ft_strdup(curr->content);
					//printf("4cmd_arg[%d]: %s\n", i, united->cmd_args[i]);
				}
				else if (is_redirect(curr->type) == 1 || curr->type == FILENAME)
					i--;
				curr = curr->next;
				i++;
			}
			united->cmd_args[i] = NULL;
		}
		united = united->next;
		//united = curr->next;
		//i = 0;
	}
	i = 0;
	temp = *token_list;
	while (temp)
	{
		if (temp->cmd_args != NULL)
		{
			while (temp->cmd_args[i])
			{
				//printf("cmd_args[%d]: %s\n", i, temp->cmd_args[i]);
				i++;
			}
		}
		temp = temp->next;
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
