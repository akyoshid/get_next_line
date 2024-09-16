/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:02 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/17 04:05:32 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOB
#  define EOB -1
# endif

typedef struct s_fd
{
	// int		fd;
	char	*leftover;
	ssize_t	lo_len;
	char	*readbuff;
	ssize_t	rb_len;
	// t_fd	*next;
}	t_fd;

char	*get_next_line(int fd);

#endif
