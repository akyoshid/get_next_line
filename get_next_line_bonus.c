/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:03:17 by akyoshid          #+#    #+#             */
/*   Updated: 2024/09/06 19:07:31 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_list	*search_fd(t_fd_list *head, int fd)
{
	t_fd_list	*result;

	return (result);
}

t_fd_list	*add_fd_node(t_fd_list *head, int fd)
{
	t_fd_list	*new_node;

	return (new_node);
}

char	*get_next_line(int fd)
{
	static t_fd_list	head;
	t_fd_list			*fd_node;

	if (fd < 0)
		return (NULL);
	fd_node = search_fd(&head, fd);
	if (fd_node == NULL)
		fd_node = add_fd_node(&head, fd);
	if (fd_node == NULL)
		return (NULL);
}
