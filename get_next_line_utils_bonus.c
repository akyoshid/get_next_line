/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:03:37 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/19 00:41:14 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// ### DESCRIPTION
// - Free `f_p->leftover` and `*p_p`, and assign NULL.
// - `p_p` will receive `&readbuff`, `&line`, or NULL.
// ### RETURN VALUE
// - Return `return_value`.
// ## ATTENTION
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
