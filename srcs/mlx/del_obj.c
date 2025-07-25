/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:02:27 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:22:45 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	delete_one(t_list **list, void *obj)
{
	t_list	*lst;
	t_list	*prev;

	prev = NULL;
	lst = *list;
	while (lst)
	{
		if (lst->content == obj)
		{
			if (prev)
				prev->next = lst->next;
			else
				*list = lst->next;
			ft_lstdelone(lst, free);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

void	destroy_obj(t_data *d, t_hit select)
{
	if (select.type == 1)
		delete_one(&d->scene.sphere, select.obj);
	else if (select.type == 2)
		delete_one(&d->scene.cylinder, select.obj);
	else if (select.type == 3)
		delete_one(&d->scene.light, select.obj);
	else if (select.type == 4)
		delete_one(&d->scene.triangle, select.obj);
	else if (select.type == 0)
		delete_one(&d->scene.plane, select.obj);
	else if (select.type == 5)
		delete_one(&d->scene.ellipsoid, select.obj);
	d->image.nb_images = 0;
}
