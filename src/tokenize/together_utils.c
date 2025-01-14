/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   together_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:04 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 17:05:16 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*all_together(t_token **token_list)
{
	t_token	*united;
	t_token	*temp;
	int		i;

	i = 0;
	united = *token_list;
	change_type(united);
	process_token_list(united);
	temp = *token_list;
	while (temp)
	{
		if (temp->cmd_args != NULL)
			while (temp->cmd_args[i])
				i++;
		temp = temp->next;
	}
	return (united);
}

void	process_token_list(t_token *united)
{
	t_token	*curr;

	while (united)
	{
		if (united->type == CMD)
		{
			curr = united;
			if (curr->content == NULL)
				curr = curr->next;
			handle_cmd_args(united, curr);
		}
		united = united->next;
	}
}

void	handle_cmd_args(t_token *uni, t_token *cur)
{
	int	i;

	i = 0;
	while (cur != NULL && cur->type != PIPE)
	{
		if (cur->next && cur->next->quote_issue_prev == 1
			&& is_redirect(cur->type) != 1 && cur->type != FILENAME)
		{
			uni->cmd_args[i] = ft_strjoin(cur->content, cur->next->content);
			cur = cur->next;
		}
		if (cur->next && cur->quote_issue_next == 1
			&& is_redirect(cur->type) != 1 && cur->type != FILENAME)
			cur = handle_lines(uni, cur, i);
		else if (is_redirect(cur->type) != 1 && cur->type != FILENAME
			&& cur->quote_issue_prev == 0 && cur->quote_issue_next == 0)
			uni->cmd_args[i] = ft_strdup(cur->content);
		else if (is_redirect(cur->type) == 1 || cur->type == FILENAME)
			i--;
		cur = cur->next;
		i++;
	}
	uni->cmd_args[i] = NULL;
}

t_token	*handle_lines(t_token *uni, t_token *cur, int i)
{
	t_token	*curr;

	curr = cur;
	if (uni->cmd_args[i])
	{
		uni->cmd_args[i] = ft_strjoin(uni->cmd_args[i], cur->next->content);
		curr = curr->next;
	}
	else
	{
		uni->cmd_args[i] = ft_strjoin(cur->content, cur->next->content);
		curr = curr->next;
	}
	return (curr);
}
