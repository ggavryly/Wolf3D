/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:09:41 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/24 14:09:42 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		exit_wlf(int code)
{
	exit(code);
}

void	init_data(t_wlf *wlf, t_calc *calc)
{
	wlf->mlx = mlx_init();
	wlf->win = mlx_new_window(wlf->mlx, WIN_W, WIN_H, "Wolf3D");
	wlf->img = mlx_new_image(wlf->mlx, WIN_W, WIN_H);
	wlf->buffer = (int *)mlx_get_data_addr(wlf->img, &wlf->tmp[0], &wlf->tmp[1], &wlf->tmp[2]);
	wlf->pos[X] += 0.5;
	wlf->pos[Y] += 0.5;
	printf("%d - X \n %d - Y\n\n PlayerX - %F || PlayerY - %F",wlf->map_size[X], wlf->map_size[Y], wlf->pos[X], wlf->pos[Y]);
	wlf->dir[X] = -1;
	wlf->dir[Y] = 0;
	wlf->plane[X] = 0;
	wlf->plane[Y] = 0.66;
	wlf->time = 0;
	wlf->oldTime = 0;
	wlf->calc = calc;
	wlf->time = 0;
	wlf->oldTime = 0;
	calc->draw[X] = 0;
	calc->draw[Y] = 0;
	calc->camera_x = 0;
	calc->ray_dir[X] = 0;
	calc->ray_dir[Y] = 0;
	calc->side_dist[X] = 0;
	calc->side_dist[Y] = 0;
	calc->delta_dist[X] = 0;
	calc->delta_dist[Y] = 0;
	calc->perpwalldist = 0;
	calc->text_select = 0;
}
