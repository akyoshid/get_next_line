/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/07 16:35:56 by akyoshid         ###   ########.fr       */
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
	return (str);
}

// *leftover_pに改行があるかを確認し、改行がなければ、改行が見つかるまでreadし続ける
// malloc失敗した場合の戻り値はNULLになっている。
// char	*get_till_eol(char *leftover, int const fd)
// {
// 	char	*buff;
// 	char	*last_p;
// 	char	*temp;

// 	buff = leftover;
// 	while (1)
// 	{
// 		last_p = ft_strchr_eol(buff);
// 		if (last_p != NULL)
// 			break ;
// 		temp = (char *)malloc(BUFFER_SIZE + 1);
// 		if (temp == NULL)
// 			return (NULL);
// 		if (read(fd, temp, BUFFER_SIZE) == 0)
// 			return (buff); // leftover == NULLの時どうする
		


// }

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// === DESCRIPTION ===
// Allocates and returns a new string by combining 's1' and 's2'.
// === MODIFICATION FOR GNL ===
// - s1 will be passed leftover, s2 will be passed read_buff.
// - Join even if (s1 == NULL).
// - Free s1 and s2 after joining.
// === RETURN VALUE ===
// When malloc was failed → Return NULL.
char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*buff;
	size_t	i;

	if (s1 == NULL)
		s1 = "";
	buff = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (*s1 == '\0')
	{
		buff[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 == '\0')
	{
		buff[i] = *s2;
		i++;
		s2++;
	}
	buff[i] = '\0';
	free(s1);
	free(s2);
	return (buff);
}

char	*gnl_split(char *leftover, char *last_p, 

// 1. 初めてfdを読むとき = (leftover == NULL)のとき
// 2. 一度読んだfdを読む時 = (leftover != NULL)のとき

// 1. 
char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*last_p;
	char		*read_buff;
	ssize_t		read_rv;

	if (fd < 0)
		return (NULL);
	// leftoverから改行文字を探して、last_pで指す。もしなければ、新しくreadして、leftoverに付け足し、もう一度改行文字を探す。
	while (1)
	{
		last_p = ft_strchr_eol(leftover);
		if (*last_p = '\n')
			break ;
		read_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (read_buff == NULL)
			return (NULL);
		read_rv = read(fd, read_buff, BUFFER_SIZE);
		if (read_rv == 0) //読むものがなくて、さらにleftoverもなかったらどうする？
			break ;
		if (read_rv == -1)
			return (NULL);
		read_buff[read_rv] = '\0';
		leftover = gnl_strjoin(leftover, read_buff);
		if (leftover == NULL)
			return (NULL);
	}
	// 改行文字でsplit
	gnl_split
}
