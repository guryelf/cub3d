/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:24:51 by fguryel           #+#    #+#             */
/*   Updated: 2024/10/17 21:17:16 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;

	if (lst == NULL)
		return ;
	head = *lst;
	while (head)
	{
		temp = head->next;
		del(head->content);
		free(head);
		head = temp;
	}
	*lst = NULL;
}
