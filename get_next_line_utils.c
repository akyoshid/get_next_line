/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:08 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/19 01:39:06 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ### DESCRIPTION
// - Free `f_p->leftover` and `*p_p`, and assign NULL.
// - `p_p` will receive `&readbuff`, `&line`, or NULL.
// ### RETURN VALUE
// - Return `return_value`.
// ### ATTENTION
// - It is guaranteed that `leftover` passed to `return_value` is not NULL.
char	*gnl_free(t_fd *f_p, char **p_p, char *return_value)
{
	if (f_p != NULL)
	{
		if (return_value != NULL)
			f_p->leftover[f_p->lo_len] = '\0';
		else
			free(f_p->leftover);
		f_p->leftover = NULL;
		f_p->lo_len = 0;
	}
	if (p_p != NULL)
	{
		free(*p_p);
		*p_p = NULL;
	}
	return (return_value);
}
