

#include "../include/minishell.h"

void	filling_a_file(int fd_heredoc, t_token *token_node, int std_in)
{
	char	*hd_input;
	int		input_size;

	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	hd_input = readline("> ");
	while (hd_input && ft_strcmp(hd_input, token_node->next->content) != 0)
	{
		input_size = ft_strlen(hd_input);
		if (input_size == 0)
			write(fd_heredoc, "\n", 1);
		else
			handle_input(fd_heredoc, hd_input, input_size);
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

void	handle_input(int fd_heredoc, char *hd_input, int input_size)
{
	if (write(fd_heredoc, hd_input, input_size) < 0)
	{
		perror(strerror(errno));
	}
	write(fd_heredoc, "\n", 1);
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
