/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:14 by star              #+#    #+#             */
/*   Updated: 2025/10/08 14:57:28 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	free_data(t_data *d)
{
	t_list		*tmp;
	t_sphere	*sphere;

	free(d->image.buf_img);
	free(d->image.mlx_img);
	tmp = d->scene.sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		if (sphere->tex.name)
			free(sphere->tex.name);
		if (sphere->tex.n_name)
			free(sphere->tex.n_name);
		tmp = tmp->next;
	}
	ft_lstclear(&d->scene.light, free);
	ft_lstclear(&d->scene.cylinder, free);
	ft_lstclear(&d->scene.plane, free);
	ft_lstclear(&d->scene.sphere, free);
	ft_lstclear(&d->scene.triangle, free);
	ft_lstclear(&d->scene.ellipsoid, free);
}
