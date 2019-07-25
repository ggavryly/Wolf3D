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

void	init_map(t_wlf *wlf)
{
	int		i;

	i = 0;
	wlf->wolf_map = (int **)malloc(sizeof(int *) *  MAP_H);
	while (i < MAP_H)
	{
		wlf->wolf_map[i] = (int *)malloc(sizeof(int) * MAP_W);
		i++;
	}
}

void	init_data(t_wlf *wlf, t_calc *calc)
{
	wlf->mlx = mlx_init();
	wlf->win = mlx_new_window(wlf->mlx, WIN_W, WIN_H, "Wolf3D");
	wlf->img = mlx_new_image(wlf->mlx, WIN_W, WIN_H);
	wlf->buffer = (int *)mlx_get_data_addr(wlf->img, &wlf->tmp[0], &wlf->tmp[1], &wlf->tmp[2]);
	wlf->player_pos[X] = 22;//x and y start position
	wlf->player_pos[Y] = 12;
	wlf->player_dir[X] = -1;//initial direction vector
	wlf->player_dir[Y] = 0;
	wlf->plane_camera[X] = 0;//the 2d raycaster version of camera plane
	wlf->plane_camera[Y] = 0.66;

	wlf->time = 0; //time of current frame
	wlf->oldTime = 0; //time of previous frame
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
}
