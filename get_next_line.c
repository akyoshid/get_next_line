/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/18 00:22:17 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char const	g_eob = EOB;

// Return the index of first EOB(-1) or EOL('\n') in `str`.
// This function requires that `str` is terminated with EOB!!!
// If `str` is NULL, return -1.
// If there is no EOL('\n') in `str` when it searches EOL, return -1.
// `is_eob` determines which one to search.
ssize_t	find_eobl(char *str, int is_eob)
{
	char	*str_s;

	str_s = str;
	if (str == NULL)
		return (-1);
	else if (is_eob == 1)
	{
		while (*str != EOB)
			str++;
		return (str - str_s);
	}
	else
	{
		while (*str != EOB)
		{
			if (*str == '\n')
				return (str - str_s);
			str++;
		}
		return (-1);
	}
}

char	*gnl_free(char **pp1, char **pp2, char *return_value, int last_wo_eol)
{
	if (pp1 != NULL)
	{
		if (last_wo_eol == 1 && *pp1 != NULL)
			(*pp1)[find_eobl(*pp1, 1)] = '\0';
		else
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

void	*ft_memcpy(void *dst, const void *src, ssize_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	ssize_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

// === DESCRIPTION ===
// - Allocates and returns a new string by combining 'leftover' and 'read_buff'.
// - lo_p will be passed &leftover, rb_p will be passed &read_buff.
// - Join even if (leftover == NULL).
// - Free leftover and read_buff after joining.
// - When malloc was failed, return NULL.

char	*gnl_strjoin(t_fd *f_p)
{
	char	*buff;

	f_p->lo_len = find_eobl(f_p->leftover, 1);
	f_p->rb_len = find_eobl(f_p->readbuff, 1);
	if (f_p->lo_len == -1)
		f_p->lo_len = 0;
	buff = (char *)malloc(f_p->lo_len + f_p->rb_len + 1);
	if (buff == NULL)
		return (gnl_free(&f_p->leftover, &f_p->readbuff, NULL, 0));
	ft_memcpy(buff, f_p->leftover, f_p->lo_len);
	ft_memcpy(buff + f_p->lo_len, f_p->readbuff, f_p->rb_len);
	buff[f_p->lo_len + f_p->rb_len] = EOB;
	return (gnl_free(&f_p->leftover, &f_p->readbuff, buff, 0));
}

// char	*gnl_strjoin(char **lo_p, char **rb_p)
// {
// 	char	*buff;
// 	ssize_t	lo_len;
// 	ssize_t	rb_len;

// 	lo_len = find_eobl(*lo_p, 1);;
// 	rb_len = find_eobl(*rb_p, 1);
// 	if (lo_len == -1)
// 		lo_len = 0;
// 	buff = (char *)malloc(lo_len + rb_len + 1);
// 	if (buff == NULL)
// 		return (gnl_free(lo_p, rb_p, NULL, 0));
// 	ft_memcpy(buff, *lo_p, lo_len);
// 	ft_memcpy(buff + lo_len, *rb_p, rb_len);
// 	buff[lo_len + rb_len] = EOB;
// 	return (gnl_free(lo_p, rb_p, buff, 0));
// }

// char *gnl_strjoin(char **lo_p, char **rb_p)
// {
// 	char	*buff;
// 	char	*lo_temp;
// 	char	*rb_temp;
// 	ssize_t	i;

// 	lo_temp = *lo_p;
// 	rb_temp = *rb_p;
// 	if (lo_temp == NULL)
// 		lo_temp = (char *)&g_eob;
// 	buff = (char *)malloc((find_eobl(lo_temp, 1) + find_eobl(rb_temp, 1) + 1));
// 	if (buff == NULL)
// 		return (gnl_free(lo_p, rb_p, NULL, 0));
// 	i = 0;
// 	while (*lo_temp != EOB)
// 		buff[i++] = *(lo_temp++);
// 	while (*rb_temp != EOB)
// 		buff[i++] = *(rb_temp++);
// 	buff[i] = EOB;
// 	return (gnl_free(lo_p, rb_p, buff, 0));
// }

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

	eol_i = find_eobl(*lo_p, 0);
	line = (char *)malloc((eol_i + 2) * sizeof(char));
	if (line == NULL)
		return (gnl_free(lo_p, NULL, NULL, 0));
	i = -1;
	while (++i <= eol_i)
		line[i] = (*lo_p)[i];
	line[eol_i + 1] = '\0';
	if ((*lo_p)[eol_i + 1] == EOB) // leftoverが全てlineに入った時の処理：空のleftoverは、空の文字列ではなく、NULLで表現する。テキストファイルに空の文字列という状態は存在しない。
		return (gnl_free(lo_p, NULL, line, 0));
	after_eol = (char *)malloc((find_eobl(*lo_p, 1) - eol_i) * sizeof(char));
	if (after_eol == NULL)
		return (gnl_free(&line, lo_p, NULL, 0));
	i = -1;
	while ((*lo_p)[eol_i + 1 + ++i] != EOB)
		after_eol[i] = (*lo_p)[eol_i + 1 + i];
	after_eol[i] = EOB;
	free(*lo_p);
	*lo_p = after_eol;
	return (line);
}

// === RETURN VALUE ===
// Return one line.
// If there is no strings to read in fd, return NULL.
// If read was failed, return NULL.
// leftoverから改行文字を探す。
// 改行文字があれば、抜ける。
// 改行文字が無ければ、新しくreadし、leftoverにstrjoinし、再度改行文字を探す。
char	*get_next_line(int fd)
{
	static t_fd	f;
	ssize_t		read_rv;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		f.lo_eol_i = find_eobl(f.leftover, 0);
		if (f.lo_eol_i != -1) // leftoverに改行文字があれば、
			return (gnl_split(&f.leftover)); // leftoverから、改行文字で切って、lineと新leftoverに分け、lineを返す
		f.readbuff = (char *)malloc(BUFFER_SIZE + 1);
		if (f.readbuff == NULL)
			return (gnl_free(&f.leftover, NULL, NULL, 0));
		read_rv = read(fd, f.readbuff, BUFFER_SIZE);
		if (read_rv == -1) // read失敗
			return (gnl_free(&f.leftover, &f.readbuff, NULL, 0));
		if (read_rv == 0) // readするものがないかつ、leftoverもない、または'\n'を含まないleftoverはある場合
			return (gnl_free(&f.leftover, &f.readbuff, f.leftover, 1));
		f.readbuff[read_rv] = EOB;
		f.leftover = gnl_strjoin(&f); // 旧leftover、read_buffはfreeされる。//🔥関数内で代入することで1行短くできる
		if (f.leftover == NULL)
			return (NULL);
	}
}
