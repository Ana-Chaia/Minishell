/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:15:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 12:56:06 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	the_exit(char **cmd, t_minishell *shellzito)
// {
// 	int		i;
// 	int		count;
// 	int		status;

// 	status = get_status(-1);
// 	count = 0;
// 	i = 1;
// 	while (cmd[i] != NULL)
// 	{
// 		while (cmd[count] != NULL)
// 			count++;
// 		if (count == 2)
// 		{
// 			if (verify_args(&cmd[1]) == 1)
// 				exit(2);
// 			else
// 			{
// 				status = ft_atoi(cmd[1]);
// 				status = mod_status(status);
// 				exit(status);
// 			}
// 		}
// 		else
// 		{
// 			if (verify_args(&cmd[1]) == 1)
// 				exit(2);
// 			ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
// 			exit(1);
// 		}
// 		i++;
// 	}
// 	if (cmd[0] && cmd[1] == NULL)
// 	{
// 		bye_bye(shellzito);
// 		status = mod_status(status);
// 		exit(status); //pegar o status de final do último cmd, 
//salvar na struct e receber ela;	
//obs: DAR FREE EM TUDO E FECHAR TODOS FDS antes de todos os exits;
// 	}
// 	return (0);
// }

int	the_exit(char **cmd, t_minishell *shellzito)
{
	int		status;
	int		i;

	i = 0;
	status = get_status(-1);
	if (cmd[1] == NULL)
	{
		bye_bye(shellzito);
		status = mod_status(status);
		exit(status);
	}
	while (cmd[i] != NULL)
			i++;
	handle_exit_args(cmd, i);
	return (0);
}

void	handle_exit_args(char **cmd, int nb_args)
{
	int		status;
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (nb_args == 2)
		{
			if (verify_args(&cmd[1]) == 1)
				exit(2);
			else
			{
				status = ft_atoi(cmd[1]);
				exit(mod_status(status));
			}
		}
		else
		{
			if (verify_args(&cmd[1]) == 1)
				exit(2);
			ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
			exit(1);
		}
		i++;
	}
}

int	mod_status(int status)
{
	int		result;

	if (status >= 0 && status <= 255)
		return (status);
	result = status % 256;
	if (status < 0)
		result += 256;
	return (result);
}

int	verify_args(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i][j])
	{
		if ((cmd[i][j]) == '+' || (cmd[i][j]) == '-')
			j++;
		if (ft_isdigit(cmd[i][j]) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "exit: numeric argument required\n");
			return (1);
		}
		if (is_longer(cmd[i]) == 1)
			return (1);
		j++;
	}
	return (0);
}
/*
int	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}
*/

int	is_longer(char *cmd)
{
	if ((ft_strlen(cmd) == 19 && ft_strncmp(cmd, "9223372036854775807", 19) > 0)
		|| ((ft_strlen(cmd) == 20 && ft_strncmp(cmd, "-9223372036854775808", 20)
				> 0)))
	{
		ft_printf_fd(STDERR_FILENO, "exit: numeric argument required\n");
		return (1);
	}
	return (0);
}
