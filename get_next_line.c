/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/15 03:28:53 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strlen(char *s)
{
	ssize_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
char	*gnl_free(char **pp1, char **pp2, char *return_value, int last_wo_eol)
{
	if (pp1 != NULL)
	{
		if (last_wo_eol != 1)
			free(*pp1);
		*pp1 = NULL;
	}
	if (pp2 != NULL)
	{
		free(*pp2);
		*pp2 = NULL;
	}
	return (return_value);
}
	
// === RETURN VALUES ===
// Return the index of the first occurrence of '\n' in s.
// If there is no '\n', return -1.
// If s is NULL, return -1.
ssize_t	find_eol_index(char *s)
{
	ssize_t	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// === DESCRIPTION ===
// - Allocates and returns a new string by combining 'leftover' and 'read_buff'.
// - lo_p will be passed &leftover, rb_p will be passed &read_buff.
// - Join even if (leftover == NULL).
// - Free leftover and read_buff after joining.
// - When malloc was failed, return NULL.
char	*gnl_strjoin(char **lo_p, char **rb_p)
{
	char	*buff;
	char	*lo_temp;
	char	*rb_temp;
	ssize_t	i;

	lo_temp = *lo_p;
	rb_temp = *rb_p;
	if (lo_temp == NULL)
		lo_temp = "";
	buff = (char *)malloc((ft_strlen(lo_temp) + ft_strlen(rb_temp) + 1));
	if (buff == NULL)
		return (gnl_free(lo_p, rb_p, NULL, 0));
	i = 0;
	while (*lo_temp != '\0')
		buff[i++] = *(lo_temp++);
	while (*rb_temp != '\0')
		buff[i++] = *(rb_temp++);
	buff[i] = '\0';
	return (gnl_free(lo_p, rb_p, buff, 0));
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
char	*gnl_split(char **lo_p)
{
	char	*line;
	char	*after_eol;
	ssize_t	eol_i;
	ssize_t	i;

	eol_i = find_eol_index(*lo_p);
	// line = (char *)malloc((eol_i + 2) * sizeof(char));
	// if (line == NULL)
		// return (gnl_free(lo_p, NULL, NULL, 0));
	// i = -1;
	// while (++i <= eol_i)
		// line[i] = (*lo_p)[i];
	// line[eol_i + 1] = '\0';
	if ((*lo_p)[eol_i + 1] == '\0') // leftoverが全てlineに入った時の処理：空のleftoverは、空の文字列ではなく、NULLで表現する。テキストファイルに空の文字列という状態は存在しない。
		return (gnl_free(lo_p, NULL, *lo_p, 1)); //NEW
		// return (gnl_free(lo_p, NULL, line, 0));
	after_eol = (char *)malloc((ft_strlen(*lo_p) - eol_i) * sizeof(char));
	if (after_eol == NULL)
		return (gnl_free(lo_p, NULL, NULL, 0)); //NEW
		// return (gnl_free(&line, lo_p, NULL, 0));
	i = -1;
	while ((*lo_p)[eol_i + 1 + ++i] != '\0')
		after_eol[i] = (*lo_p)[eol_i + 1 + i];
	after_eol[i] = '\0';
	// free(*lo_p);
	line = *lo_p; //NEW
	line[eol_i + 1] = '\0'; //NEW
	*lo_p = after_eol;
	return (line);
}

// char	*gnl_split(char **lo_p)
// {
// 	char	*line;
// 	char	*after_eol;
// 	ssize_t	eol_i;
// 	ssize_t	i;

// 	eol_i = find_eol_index(*lo_p);
// 	line = (char *)malloc((eol_i + 2) * sizeof(char));
// 	if (line == NULL)
// 		return (gnl_free(lo_p, NULL, NULL, 0));
// 	i = -1;
// 	while (++i <= eol_i)
// 		line[i] = (*lo_p)[i];
// 	line[eol_i + 1] = '\0';
// 	if ((*lo_p)[eol_i + 1] == '\0') // leftoverが全てlineに入った時の処理：空のleftoverは、空の文字列ではなく、NULLで表現する。テキストファイルに空の文字列という状態は存在しない。
// 		return (gnl_free(lo_p, NULL, line, 0));
// 	after_eol = (char *)malloc((ft_strlen(*lo_p) - eol_i) * sizeof(char));
// 	if (after_eol == NULL)
// 		return (gnl_free(&line, lo_p, NULL, 0));
// 	i = -1;
// 	while ((*lo_p)[eol_i + 1 + ++i] != '\0')
// 		after_eol[i] = (*lo_p)[eol_i + 1 + i];
// 	after_eol[i] = '\0';
// 	free(*lo_p);
// 	*lo_p = after_eol;
// 	return (line);
// }

// === RETURN VALUE ===
// Return one line.
// If there is no strings to read in fd, return NULL.
// If read was failed, return NULL.
// leftoverから改行文字を探す。
// 改行文字があれば、抜ける。
// 改行文字が無ければ、新しくreadし、leftoverにstrjoinし、再度改行文字を探す。
char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*read_buff;
	ssize_t		read_rv;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	while (1)
	{
		if (find_eol_index(leftover) != -1) // leftoverに改行文字があれば、
			return (gnl_split(&leftover)); // leftoverから、改行文字で切って、lineと新leftoverに分け、lineを返す
		read_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (read_buff == NULL)
			return (gnl_free(&leftover, NULL, NULL, 0));
		read_rv = read(fd, read_buff, BUFFER_SIZE);
		if (read_rv == -1 || (read_rv == 0 && leftover == NULL)) //read失敗 || readするものがなくleftoverもない
			return (gnl_free(&leftover, &read_buff, NULL, 0));
		if (read_rv == 0) // readするものがないが、('\n'は含まれていない)leftoverはある場合
			return (gnl_free(&leftover, &read_buff, leftover, 1));
		read_buff[read_rv] = '\0';
		leftover = gnl_strjoin(&leftover, &read_buff); //旧leftover、read_buffはfreeされる。
		if (leftover == NULL)
			return (NULL);
	}
}
