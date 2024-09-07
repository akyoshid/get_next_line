/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:05 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/07 17:30:38 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// === RETURN VALUES ===
// Return a pointer to the first occurrence of '\n' in s.
// If there is no '\n', return a pointer to the null terminator in s.
// If s is NULL, return NULL.
char	*gnl_strchr(char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (s);
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
// leftoverがNULLの時は、呼び出しもとの関数が終了しているはずなので、想定しない
// lastは必ず
// つまり、leftoverには必ず文字列があり、lastも'\n'か'\0'を指している。
char	*gnl_split(char **leftover_p, char *last)
{
	char	*line;
	size_t	i;

	if (*last == '\n')

	line = (char *)malloc(last - *leftover_p);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (leftover_p[i] != last)
	{
		line[i]
}

// 1. 初めてfdを読むとき = (leftover == NULL)のとき
// 2. 一度読んだfdを読む時 = (leftover != NULL)のとき

// 1. 
char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*last;
	char		*read_buff;
	ssize_t		read_rv;

	if (fd < 0)
		return (NULL);
	// leftoverから改行文字を探して、lastで指す。もしなければ、新しくreadして、leftoverに付け足し、もう一度改行文字を探す。
	while (1)
	{
		last = gnl_strchr(leftover);
		if (*last = '\n') // lastが改行文字、つまりleftoverに改行文字が含まれている時のみ、breakし、次に行く。
			break ;
		read_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (read_buff == NULL)
			return (NULL);
		read_rv = read(fd, read_buff, BUFFER_SIZE);
		if (read_rv == -1 || (read_rv == 0 && leftover == NULL)) //read失敗、もしくはreadするものがなく、leftoverもない場合
			return (NULL);
		if (read_rv == 0) // readするものがなかったけど、('\n'は含まれていない)leftoverはある場合
			return (leftover);
		read_buff[read_rv] = '\0';
		leftover = gnl_strjoin(leftover, read_buff);
		if (leftover == NULL)
			return (NULL);
	}
	// splitは、leftoverから、改行文字で切って、lineと新leftoverに分ける。
	gnl_split(&leftover, last);
	// gnl_splitで、malloc失敗した場合の処理
}
