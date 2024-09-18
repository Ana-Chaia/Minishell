/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:29 by jbolanho          #+#    #+#             */
/*   Updated: 2024/09/18 16:16:05 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	search_heredoc(t_token **token_list)
{
	t_token	*curr;

	curr = *token_list;
	while (curr)
	{
		if (curr->type == HEREDOC)
			is_heredoc (curr);
		curr = curr->next;
	}
}

void	is_heredoc(t_token *token_node)
{
	t_token	*heredoc;
	char	*file_name;

	heredoc = token_node;
	while (heredoc)
	{
		file_name = create_file_name();
		
	}

}

char	*create_file_name(void)
{
	char		*dir;
	char		*nbr;
	char		*name;
	static int	nbr_cmd;

	nbr = ft_itoa(nbr_cmd);
	dir = "/tmp/heredoc";
	name = ft_strjoin(dir, nbr);
	free (nbr);
	nbr_cmd++;
	printf("%s\n", name);
	return (name);
}