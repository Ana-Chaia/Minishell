/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:43:55 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/23 13:30:03 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	result = (char *)malloc((s_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
