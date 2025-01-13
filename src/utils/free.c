/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:12:08 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/19 11:53:03 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bye_bye(t_minishell *mini)
{
	char	**env_copy;
	int		fd;

	fd = STDIN_FILENO;
	env_copy = env_shellzito(NULL);
	if (mini->input)
		free(mini->input);
	if (env_copy)
		free_ptrptr(env_copy);
	if (mini->tree)
	{
		free_ast(mini->tree);
	}
	if (mini->export_list)
	{
		free_export(mini->export_list);
	}
	if (mini->tokenlist)
		free_tokenlist(mini->tokenlist);
	if (mini)
		free(mini);
	close_fds(fd);
}

void	free_ptrptr(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

int	ft_flags(int fd, char flag, va_list args)
{
	if (flag == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	if (flag == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	if (flag == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

int	ft_printf_fd(int fd, const char *type_format, ...)
{
	va_list	args;
	int		i;
	int		result;

	i = 0;
	result = 0;
	if (!type_format)
		return (-1);
	va_start(args, type_format);
	while (type_format[i])
	{
		if (type_format[i] == '%' && type_format[i + 1] != '\0')
			result += ft_flags(fd, type_format[++i], args);
		else
			result += ft_putchar_fd(type_format[i], fd);
		i++;
	}
	va_end(args);
	return (result);
}
