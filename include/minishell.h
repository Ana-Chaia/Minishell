
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "tokenize.h"
# include "redirect.h"
# include "ast.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

#include <fcntl.h>   // Para O_CREAT, O_RDWR, O_TRUNC
#include <errno.h>   // Para errno
#include <string.h>  // Para strerror

void	init_struct(t_minishell *mini);
void	clear_and_free(t_minishell *mini);
void	take_token(char *input);
void	free_tokenlist(t_token *tokenlist);
// apagar printer
void	ft_tree_printer(t_ast *root);

#endif