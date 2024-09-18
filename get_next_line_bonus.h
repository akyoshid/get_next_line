/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:03:54 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/19 00:46:10 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
	int		fd;
	char	*leftover;
	ssize_t	lo_len;
	ssize_t	lo_eol_i;
	char	*readbuff;
	ssize_t	rb_len;
	t_fd	*prev;
	t_fd	*next;
}	t_fd;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, ssize_t n);
ssize_t	find_eol(char *str);
char	*gnl_strjoin(t_fd *f_p);
char	*gnl_split(t_fd *f_p);
char	*gnl_free(t_fd *f_p, char **p_p, char *return_value);

#endif
