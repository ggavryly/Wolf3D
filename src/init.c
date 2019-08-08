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

int		key_release(int key, t_wlf *wlf)
{
	if (key == KEY_D)
		wlf->keys.d = false;
	if (key == KEY_A)
		wlf->keys.a = false;
	if (key == KEY_W)
		wlf->keys.w = false;
	if (key == KEY_S)
		wlf->keys.s = false;
	if (key == SHIFT)
		wlf->keys.shift = false;
	return (0);
}

int		exit_wlf(int code)
{
	if (code == 1)
		ft_putendl("Invalid File");
	else if (code == 2)
		ft_putendl("Usage: ./wolf3d [map_file]");
	else if (code == 3)
		ft_putendl("Invalid Map");
	system("killall afplay &> /dev/null");
	exit(code);
}

void	init_data(t_wlf *w, t_calc *calc)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, WIN_W, WIN_H, "Wolf3D");
	w->img = mlx_new_image(w->mlx, WIN_W, WIN_H);
	w->buffer = (int *)mlx_get_data_addr(w->img,
			&w->tmp[0], &w->tmp[1], &w->tmp[2]);
	w->pos[X] += 0.5;
	w->pos[Y] += 0.5;
	w->dir[X] = -1;
	w->dir[Y] = 0;
	w->plane[X] = 0;
	w->plane[Y] = 0.66;
	w->time = 0;
	w->old_time = 0;
	w->calc = calc;
	w->time = 0;
	w->old_time = 0;
	calc->draw[X] = 0;
	calc->draw[Y] = 0;
	calc->camera_x = 0;
	calc->move_speed = 0.10;
	calc->rot_speed = 0.04;
}
