/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:02 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/19 00:35:09 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOB
#  define EOB -1
# endif

typedef struct s_fd
{
	char	*leftover;
	ssize_t	lo_len;
	ssize_t	lo_eol_i;
	char	*readbuff;
	ssize_t	rb_len;
}	t_fd;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, ssize_t n);
ssize_t	find_eol(char *str);
char	*gnl_strjoin(t_fd *f_p);
char	*gnl_split(t_fd *f_p);
char	*gnl_free(t_fd *f_p, char **p_p, char *return_value);

#endif
