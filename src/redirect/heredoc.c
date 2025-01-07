/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:29 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/18 12:04:57 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

void	search_heredoc(t_token **token_list)
{
	t_token	*curr;

	curr = *token_list;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			is_heredoc (curr);
			break ;
		}
		curr = curr->next;
	}
}
/*
void	is_heredoc(t_token *token_node)
{
	t_token	*heredoc;
	char	*file_name;
	int		fd_heredoc;
	int		std_in;

	heredoc = token_node;
	std_in = dup(STDIN_FILENO);
	while (heredoc != NULL)
	{
		if (heredoc->type == HEREDOC)
		{
			file_name = create_file_name();
			fd_heredoc = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
			if (fd_heredoc < 0)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %s\n",
					file_name, strerror(errno));
				get_status(1);
			}
			filling_a_file(fd_heredoc, heredoc, std_in);
			free(heredoc->next->content);
			heredoc->next->content = ft_strdup(file_name);
			heredoc->next->type = FILENAME;
			if (g_signal == SIGINT)
				unlink(file_name);
			free(file_name);
		}
		heredoc = heredoc->next;
	}
}
*/

void	is_heredoc(t_token *token_node)
{
	t_token	*heredoc;
	int		std_in;

	heredoc = token_node;
	std_in = dup(STDIN_FILENO);
	while (heredoc != NULL)
	{
		if (heredoc->type == HEREDOC)
			handle_heredoc(heredoc, std_in);
		heredoc = heredoc->next;
	}
}

void	handle_heredoc(t_token *heredoc, int std_in)
{
	char	*file_name;
	int		fd_heredoc;

	file_name = create_file_name();
	fd_heredoc = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd_heredoc < 0)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file_name, strerror(errno));
		get_status(1);
	}
	filling_a_file(fd_heredoc, heredoc, std_in);
	free(heredoc->next->content);
	heredoc->next->content = ft_strdup(file_name);
	heredoc->next->type = FILENAME;
	if (g_signal == SIGINT)
		unlink(file_name);
	free(file_name);
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
	return (name);
}
