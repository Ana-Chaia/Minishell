/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:51:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/07 12:59:29 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_type(t_token *united)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = united;
	while (temp)
	{
		//if ((temp->prev == NULL || temp->prev->type == PIPE) && temp->type != RED_IN)
		if ((temp->prev == NULL || temp->prev->type == PIPE) && is_redirect(temp->type) == 0)
			temp->type = CMD;
		//if (temp->prev == NULL && temp->type != RED_IN)
		//criar outra regra para CMD com redirecionamento;
		if (temp->prev != NULL && (temp->prev->type == RED_IN
			|| temp->prev->type == RED_OUT || temp->prev->type == APPEND))
			temp->type = FILENAME;
		//if (temp->prev != NULL && (temp->prev->type == HEREDOC))
			//temp->type = FILENAME;
		temp = temp->next;
	}
	//printf("temp->type 1= %i\n", temp->type);
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

void	del(void *content)
{
	free(content);
}


t_token	*all_together(t_token **token_list)
{
	t_token	*united;
	t_token	*curr;
	//char 	*space;
	char	*temp;

	united = *token_list;
	change_type(united);
	//space = ft_strdup(" ");
	while (united)
	{
		if (united->type == CMD)
		{
			curr = united;
			while (curr != NULL && curr->type != PIPE)
			{
				if ((curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 1)
				{
					temp = united->content;
					united->content = ft_strjoin(united->content,
							curr->content);
					free(temp);
				}
				if (curr->prev && (curr->prev->type == S_QUOTES || curr->prev->type == D_QUOTES || curr->prev->type == CMD) && curr->prev->quote_issue == 2)
				{
					temp = united->content;
					united->content = ft_strjoin(united->content,
							curr->content);
					free(temp);
				}
				else if ((curr->type == WORD || curr->type == S_QUOTES || curr->type == D_QUOTES) && curr->quote_issue == 0)
				{
					temp = united->content;
					united->content = ft_strjoin(united->content, " ");
					free(temp);
					temp = united->content;
					united->content = ft_strjoin(united->content,
							curr->content);
					free(temp);
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
