/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/12 11:47:32 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	united->cmd_args = (char **)malloc(sizeof(char *) *  i + 1);
	i = 0;
	temp = united;
	while (temp)
	{
		if ((temp->prev == NULL || temp->prev->type == PIPE)
			&& is_redirect(temp->type) == 0)
		{
			temp->type = CMD;
			united->cmd_args[0] = ft_strdup(temp->content);
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
	// while (united)
	// {
	// 	i++;
	// 	united = united->next;
	// }
	// cmd_args = (t_token **)malloc(sizeof(char *) *  i);
	// i = 1;
	while (united)
	{
		if (united->type == CMD)
		{
			curr = united;
			while (curr != NULL && curr->type != PIPE)
			{
				if ((curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 1)
				{
					//temp = united->content;
					//united->content = ft_strjoin(united->content,
							//curr->content);
					united->cmd_args[i] = ft_strjoin(united->cmd_args[i - 1], curr->content);
					//free(temp);
				}
				if (curr->prev && (curr->prev->type == S_QUOTES || curr->prev->type == D_QUOTES || curr->prev->type == CMD) && curr->prev->quote_issue == 2)
				{
					//temp = united->content;
					//united->content = ft_strjoin(united->content,
							//curr->content);
					united->cmd_args[i] = ft_strjoin(united->cmd_args[i - 1], curr->content);
					//free(temp);
				}
				else if ((curr->type == WORD || curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 0)
				{
					//temp = united->content;
					//united->content = ft_strjoin(united->content, " ");
					united->cmd_args[i] = ft_strdup(curr->content);
					//free(temp);
					//temp = united->content;
					//united->content = ft_strjoin(united->content,
							//curr->content);
					//free(temp);
				}
				i++;
				curr = curr->next;
			}
			united->cmd_args[i] = NULL;
		}
		united = united->next;
	}
	i = 0;
	temp = *token_list;
	while (temp)
	{
		if (temp->cmd_args != NULL)
		{
			while (temp->cmd_args[i])
			{
				printf("cmd_args[%d]: %s\n", i, temp->cmd_args[i]);
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
