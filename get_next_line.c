/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/07 23:27:36 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// === RETURN VALUES ===
// Return the index of the first occurrence of '\n' in s.
// If there is no '\n', return -1.
// If s is NULL, return -1.
size_t	find_eol_index(char *s)
{
	size_t	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		s++;
	}
	return (-1);
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

// === RETURN VALUE ===
// Return a string that extracts from leftover to the first '\n'.
// (The string is null-terminated.)
// Also, put the remaining string after the first '\n'
// into the pointer variable leftover of the calling function
// through the double pointer argument.
// If malloc was failed, it returns NULL.
// leftoverは確実に
// - NULLではない。
// - 改行文字が含まれている。
char	*gnl_split(char **leftover_p)
{
	char	*line;
	char	*after_eol;
	size_t	eol_i;
	size_t	i;

	eol_i = find_eol_index(*leftover_p);
	line = (char *)malloc((eol_i + 2) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < eol_i)
	{
		line[i] = *leftover_p[i];
		i++;
	}
	line[eol_i] = '\n';
	line[eol_i + 1] = '\0';
	if (*leftover_p[eol_i + 1] == '\0') // ピッタリなくなった時の処理
	{
		free(*leftover_p);
		*leftover_p = NULL;
		return (line);
	}
	after_eol = (char *)malloc((ft_strlen(*leftover_p) - eol_i) * sizeof(char));
	if (after_eol == NULL) // freeしないと！🔥🔥🔥🔥🔥malloc失敗した後のfree頑張ろ
		return (NULL);
	i = 0;
	while (*leftover_p[eol_i + 1 + i] != '\0')
	{
		after_eol[i] = *leftover_p[eol_i + 1 + i];
		i++;
	}
	after_eol[i] = '\0';
	free(*leftover_p);
	*leftover_p = after_eol;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*read_buff;
	ssize_t		read_rv;

	if (fd < 0)
		return (NULL);
	// leftoverから改行文字を探す。
	// 改行文字があれば、抜ける。
	// 改行文字が無ければ、新しくreadし、leftoverにstrjoinし、再度改行文字を探す。
	while (1)
	{
		if (find_eol_index(leftover) != -1) // leftoverに改行文字があれば、breakし、次に行く。
			break ;
		read_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (read_buff == NULL)
			return (NULL);
		read_rv = read(fd, read_buff, BUFFER_SIZE);
		if (read_rv == -1 || (read_rv == 0 && leftover == NULL)) //read失敗 || readするものがなくleftoverもない
			return (NULL);
		if (read_rv == 0) // readするものがないが、('\n'は含まれていない)leftoverはある場合
			return (leftover);
		read_buff[read_rv] = '\0';
		leftover = gnl_strjoin(leftover, read_buff);
		if (leftover == NULL)
			return (NULL);
	}
	// ここには、必ず改行文字が含まれたleftoverが来ている。
	// splitは、leftoverから、改行文字で切って、lineと新leftoverに分ける。
	gnl_split(&leftover);
	// gnl_splitで、malloc失敗した場合の処理
}
