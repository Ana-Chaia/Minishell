/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:59:03 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/01 15:45:27 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast
{
	int				type;
	char			*content;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
	// struct s_ast	*child;
}				t_ast;


t_token	*token_to_ast(t_token *tokenlist);
t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist);
t_ast	*ast_new_node(t_token *token_node);
int		is_redirect(t_token	*curr);


#endif