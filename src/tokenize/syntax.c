/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:50:04 by anacaro5          #+#    #+#             */
/*   Updated: 2024/09/20 10:55:24 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax(t_token **token_list)
{
	t_token	*curr;

	curr = *token_list;
	while (curr)
	{
		if (pipe_syntax(curr))
		{
			free_tokenlist(*token_list);
			return (1);
		}
		if (chevron_syntax(curr))
		{
			free_tokenlist(*token_list);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}


int	pipe_syntax(t_token *token_node)
{
	if (token_node->type == PIPE)
	{
		if (!token_node->prev)
		{
			ft_putstr_fd("shellzito: syntax error near unexpected token `|'\n",
				2);
			return (1);
		}
		if (ft_strncmp (token_node->prev->content, "|", 1) == 0)
		{
			ft_putstr_fd("shellzito: syntax error near unexpected token `||'\n",
				2);
			return (1);
		}	
		if (!token_node->next || token_node->prev->type != WORD)
		{
			ft_putstr_fd("shellzito: syntax error near unexpected token `|'\n",
				2);
			return (1);
		}
	}
	return (0);
}

int	chevron_syntax(t_token *token_node)
{
	if (token_node->type == APPEND || token_node->type == RED_OUT
		|| token_node->type == RED_IN || token_node->type == HEREDOC)
	{
		if (!token_node->next)
		{
			ft_putstr_fd("shellzito: syntax error near token `newline'\n", 2);
			return (1);
		}
		if (token_node->type == APPEND && token_node->next->type == RED_OUT)
		{	
			ft_putstr_fd("shellzito: syntax error near unexpected token `>'\n",
				2);
			return (1);
		}
		if (token_node->type == HEREDOC && token_node->next->type == RED_IN)
		{
			ft_putstr_fd("shellzito: syntax error near token `newline'\n", 2);
			return (1);
		}
	}
	return (0);
}
