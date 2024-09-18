
#ifndef REDIRECT_H
# define REDIRECT_H

void	search_heredoc(t_token **token_list);
void	is_heredoc(t_token *token_node);
char	*create_file_name(void);

#endif