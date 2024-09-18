/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/18 05:40:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

// 🔥
// readするものがないかつ、leftoverもない、または'\n'を含まないleftoverはある場合
// BONUS:読み切ったら、もしくはエラーが生じたら、ノードもfreeしないといけない
char	*gnl_free(char **pp1, char **pp2, char *return_value, int last_wo_eol)
{
	if (pp1 != NULL)
	{
		if (last_wo_eol == 1)
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
// - Allocate & return new string by combining 'leftover' and 'read_buff'.
// - The string is terminated by EOB.
// - Join even if (leftover == NULL).
// - Free old leftover and read_buff after joining.
// - Store new string in leftover.
// - Store the length of new string in lo_len;
// - When malloc was failed, return NULL.
char	*gnl_strjoin(t_fd *f_p)
{
	char	*buff;

	f_p->lo_len = find_eobl(f_p->leftover, 1);
	if (f_p->lo_len == -1)
		f_p->lo_len = 0;
	buff = (char *)malloc(f_p->lo_len + f_p->rb_len + 1);
	if (buff == NULL)
		return (gnl_free(&f_p->leftover, &f_p->readbuff, NULL, 0));
	ft_memcpy(buff, f_p->leftover, f_p->lo_len);
	ft_memcpy(buff + f_p->lo_len, f_p->readbuff, f_p->rb_len);
	buff[f_p->lo_len + f_p->rb_len] = EOB;
	gnl_free(&f_p->leftover, &f_p->readbuff, NULL, 0);
	f_p->leftover = buff;
	f_p->lo_len += f_p->rb_len;
	return (f_p->leftover);
}

// === DESCRIPTION ===
// - Return the string up to first '\n' from leftover.
// - The string is null-terminated.
// - Also, store remaining string after first '\n' into leftover.
// - The string is terminated by EOB.
// - When malloc was failed, return NULL.
// - The leftover processed by this function is guaranteed
// to be not NULL & to contain '\n'.
// - When entire leftover is stored in line,
// that is, when the new leftover becomes empty,
// store NULL, not empty string.
char	*gnl_split(t_fd *f_p)
{
	char	*line;
	char	*after_eol;
	size_t	after_eol_len;

	line = (char *)malloc((f_p->lo_eol_i + 2));
	if (line == NULL)
		return (gnl_free(&f_p->leftover, NULL, NULL, 0));
	ft_memcpy(line, f_p->leftover, f_p->lo_eol_i + 1);
	line[f_p->lo_eol_i + 1] = '\0';
	if (f_p->leftover[f_p->lo_eol_i + 1] == EOB)
		return (gnl_free(&f_p->leftover, NULL, line, 0));
	after_eol_len = f_p->lo_len - f_p->lo_eol_i - 1;
	after_eol = (char *)malloc(after_eol_len + 1);
	if (after_eol == NULL)
		return (gnl_free(&f_p->leftover, &line, NULL, 0));
	ft_memcpy(after_eol, f_p->leftover + f_p->lo_eol_i + 1, after_eol_len);
	after_eol[after_eol_len] = EOB;
	free(f_p->leftover);
	f_p->leftover = after_eol;
	f_p->lo_len = after_eol_len;
	return (line);
}

// === RETURN VALUE ===
// - Return one line.
// - If there is no strings to read in fd, return NULL.
// - If an error occurs, return NULL.
// - When NULL is returned, the file descriptor should be closed,
// so if an error occurs, all heap memory are freed.
// === DESCRIPTION ===
// 1. Find for '\n' in leftover.
// 2. If there is '\n', split and return the string up to '\n'.
// 3. If there is no '\n', read from fd.
// 4. If there is nothing else to read, return leftover.
// 5. Join readbuff with leftover and back to step 1.
char	*get_next_line(int fd)
{
	static t_fd	f;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		f.lo_eol_i = find_eobl(f.leftover, 0);
		if (f.lo_eol_i != -1)
			return (gnl_split(&f));
		f.readbuff = (char *)malloc(BUFFER_SIZE + 1);
		if (f.readbuff == NULL)
			return (gnl_free(&f.leftover, NULL, NULL, 0));
		f.rb_len = read(fd, f.readbuff, BUFFER_SIZE);
		if (f.rb_len == -1 || (f.rb_len == 0 && f.leftover == NULL))
			return (gnl_free(&f.leftover, &f.readbuff, NULL, 0));
		else if (f.rb_len == 0 && f.leftover != NULL)
			return (gnl_free(&f.leftover, &f.readbuff, f.leftover, 1));
		else if (gnl_strjoin(&f) == NULL)
			return (NULL);
	}
}
