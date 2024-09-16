/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:29 by jbolanho          #+#    #+#             */
/*   Updated: 2024/09/16 16:29:31 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	search_heredoc(t_token **token_list)
{
	t_token	*curr;

	curr == token_list;
	while (curr)
	{
		if (curr->type == HEREDOC)
			is_heredoc (curr);
		curr = curr->next;
	}
}

void	is_heredoc(t_token *token_node)
{
	t_token

}