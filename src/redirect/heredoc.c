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
			
			// init_signal_heredoc(fd_heredoc);
			if (fd_heredoc < 0)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %s\n", file_name, strerror(errno));
				//ft_printf("Shellzito: %s: %s\n", file_name, strerror(errno));
				get_status(1);
			}
			filling_a_file(fd_heredoc, heredoc, std_in);
			free(heredoc->next->content);
			heredoc->next->content = ft_strdup(file_name);
			heredoc->next->type = FILENAME;
			if(g_signal == SIGINT)
				unlink(file_name);
			free(file_name);
		}
		heredoc = heredoc->next;
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
	//printf("%s\n", name);
	return (name);
}

void	filling_a_file(int fd_heredoc, t_token *token_node, int std_in)
{
	char	*hd_input;
	int		input_size;

	//init_signal();
	//init_signal_heredoc(fd_heredoc);
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	hd_input = readline("> ");
	//ctrld(hd_input, fd_heredoc, token_node);
	/*
	if (hd_input == NULL)
	{
		printf("shellzito: warning: here-document delimited by end-of-file (wanted `%s')\n", token_node->next->content);
		close(fd_heredoc);
		//get_status(0);
		return ;
	}
	*/
	// if (g_signal == SIGINT)
	// {
	// 	dup2(std_in, STDIN_FILENO);
	// 	// if(hd_input)
	// 	// // {
	// 	// // 	free(hd_input);
	// 	// // 	hd_input = NULL;
	// 	// // }
	// 	close(fd_heredoc);
	// }
	while (hd_input && ft_strcmp(hd_input, token_node->next->content) != 0)
	{
		input_size = ft_strlen(hd_input);
		if (input_size == 0)
			write(fd_heredoc, "\n", 1);
		else
		{	
			if (write(fd_heredoc, hd_input, input_size) < 0)
			{
				perror(strerror(errno));
			}
			write(fd_heredoc, "\n", 1);
		}
		// init_signal();
		// if (hd_input && ft_strcmp(hd_input, token_node->next->content) == 0)
		// {
		// 	free(hd_input);
		// 	write(fd_heredoc, "\n\0", 2);
		//ctrld(hd_input, fd_heredoc, token_node);
		// 	close(fd_heredoc);
		// 	printf("teste input vazio\n");
		// 	break ;
		// }
		// write (fd_heredoc, "\n", 1);
		free(hd_input);
		hd_input = readline("> ");
	}
	if (hd_input == NULL)
		ctrld(fd_heredoc, token_node, std_in);
	if (hd_input)
	{
		free(hd_input);
		close(fd_heredoc);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (s1 && s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		if ((unsigned char)*s1 == '\0' && (unsigned char)*s2 == '\0')
			return (0);
	}
	return (0);
}

