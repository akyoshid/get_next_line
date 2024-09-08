/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/08 17:01:54 by akyoshid         ###   ########.fr       */
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

char	*gnl_free(char **pp1, char **pp2) //Return Valueを設定できる引数用意すれば、get_next_lineの行数減らせる
{
	free(*pp1);
	free(*pp2);
	*pp1 = NULL;
	*pp2 = NULL;
	return (NULL);
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
// - Allocates and returns a new string by combining 'leftover' and 'read_buff'.
// - lo_p will be passed &leftover, rb_p will be passed &read_buff.
// - Join even if (leftover == NULL).
// - Free leftover and read_buff after joining.
// - When malloc was failed, return NULL.
char	*gnl_strjoin(char const **lo_p, char const **rb_p)
{
	char	*buff;
	char	*lo_temp;
	char	*rb_temp;
	size_t	i;

	lo_temp = *lo_p;
	rb_temp = *rb_p;
	if (lo_temp == NULL)
		lo_temp = "";
	buff = (char *)malloc((ft_strlen(*lo_temp) + ft_strlen(*rb_temp) + 1));
	if (buff == NULL)
		return (gnl_free(lo_p, rb_p));
	i = 0;
	while (*lo_temp != '\0')
		buff[i++] = *(lo_temp++);
	while (*rb_temp != '\0')
		buff[i++] = *(rb_temp++);
	buff[i] = '\0';
	gnl_free(lo_p, rb_p);
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

// === RETURN VALUE ===
// Return one line.
// If there is no strings to read in fd, return NULL.
// If read was failed, return NULL.
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
			return (gnl_free(&leftover, NULL));
		read_rv = read(fd, read_buff, BUFFER_SIZE);
		if (read_rv == -1 || (read_rv == 0 && leftover == NULL)) //read失敗 || readするものがなくleftoverもない 🔥leftover == NULLの時に残りがないって判断は正しい？gnl_splitでleftoverを正しく処理できていれば問題ないよ
			return (gnl_free(&leftover, &read_buff));
		if (read_rv == 0) // readするものがないが、('\n'は含まれていない)leftoverはある場合 🔥上の次考えて 🔥gnl_freeの引数増やせば行減らせるよ
		{
			free(read_buff);
			return (leftover);
		}
		read_buff[read_rv] = '\0';
		leftover = gnl_strjoin(&leftover, &read_buff);
		if (leftover == NULL)
			return (NULL);
	}
	// ここには、必ず改行文字が含まれたleftoverが来ている。read_buffはfree済みか割当なし。
	// splitは、leftoverから、改行文字で切って、lineと新leftoverに分ける。
	gnl_split(&leftover);
	// gnl_splitで、malloc失敗した場合の処理
}
