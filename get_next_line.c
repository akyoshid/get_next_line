/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/06 21:48:19 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_eol(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

// *leftover_pに改行があるかを確認し、改行がなければ、改行が見つかるまでreadし続ける
// malloc失敗した場合の戻り値はNULLになっている。
char	*get_till_eol(char **leftover_p, int const fd)
{
	char	*buff;
	char	*last_p;
	char	*temp;

	while (1)
	{
		last_p = ft_strchr_eol(*leftover_p);
		if (last_p != NULL)
			break ;
		temp = (char *)malloc(BUFFER_SIZE + 1);
		if (temp == NULL)
			return (NULL);
		if (read(fd, temp, BUFFER_SIZE) == 0)
			break ;
		


}



char	*get_next_line(int fd)
{
	static char	*leftover;

	if (fd < 0)
		return (NULL);
}
