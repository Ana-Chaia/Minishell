
#ifndef REDIRECT_H
# define REDIRECT_H

void	search_heredoc(t_token **token_list);
void	is_heredoc(t_token *token_node);
char	*create_file_name(void);
void	filling_a_file(int fd_heredoc, t_token *token_node);
int		ft_strcmp(const char *s1, const char *s2);





#endif