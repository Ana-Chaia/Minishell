/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:59:03 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/18 13:56:58 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast
{
	//int				*type;
	int				type;
	char			*content;
	char			*first_cmd;
	char			*exec_ready;
	char			**cmd_args;
	char			**path_array;
	struct s_ast	*left;
	struct s_ast	*right;
	//struct s_ast	*parent;
	// struct s_ast	*child;
}				t_ast;


t_token	*pipe_to_ast(t_token *tokenlist);
t_token	*redir_to_ast(t_token *tokenlist);
t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist);
t_ast	*ast_new_node(t_token *token_node);
int		is_redirect(int curr);
t_token *find_last_one (t_token *tokenlist);



#endif