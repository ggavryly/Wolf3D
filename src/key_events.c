/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 16:18:36 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/24 16:18:38 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		key_event(int key, t_wlf *wlf)
{
//	mlx_clear_window(wlf->mlx, wlf->win);
	if (key == KEY_UP)
	{
		if(worldMap[(int)(wlf->pos[X] + wlf->dir[X] * wlf->calc->move_speed)][(int)(wlf->pos[Y])] == 0)
			wlf->pos[X] += wlf->dir[X] * wlf->calc->move_speed;
		if(worldMap[(int)(wlf->pos[X])][(int)(wlf->pos[Y] + wlf->dir[Y] * wlf->calc->move_speed)] == 0)
			wlf->pos[Y] += wlf->dir[Y] * wlf->calc->move_speed;
	}
	//move backwards if no wall behind you
	if (key == KEY_DOWN)
	{
		if(worldMap[(int)(wlf->pos[X] - wlf->dir[X] * wlf->calc->move_speed)][(int)(wlf->pos[Y])] == 0)
			wlf->pos[X] -= wlf->dir[X] * wlf->calc->move_speed;
		if(worldMap[(int)(wlf->pos[X])][(int)(wlf->pos[Y] - wlf->dir[Y] * wlf->calc->move_speed)] == 0)
			wlf->pos[Y] -= wlf->dir[Y] * wlf->calc->move_speed;
	}
	//rotate to the right
	if (key == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		wlf->calc->old_dir = wlf->dir[X];
		wlf->dir[X] = wlf->dir[X] * cos(-wlf->calc->rot_speed) - wlf->dir[Y] * sin(-wlf->calc->rot_speed);
		wlf->dir[Y] = wlf->calc->old_dir * sin(-wlf->calc->rot_speed) + wlf->dir[Y] * cos(-wlf->calc->rot_speed);
		wlf->calc->old_plane = wlf->plane[X];
		wlf->plane[X] = wlf->plane[X] * cos(-wlf->calc->rot_speed) - wlf->plane[Y] * sin(-wlf->calc->rot_speed);
		wlf->plane[Y] = wlf->calc->old_plane * sin(-wlf->calc->rot_speed) + wlf->plane[Y] * cos(-wlf->calc->rot_speed);
	}
	//rotate to the left
	if (key == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		wlf->calc->old_dir = wlf->dir[X];
		wlf->dir[X] = wlf->dir[X] * cos(wlf->calc->rot_speed) - wlf->dir[Y] * sin(wlf->calc->rot_speed);
		wlf->dir[Y] = wlf->calc->old_dir * sin(wlf->calc->rot_speed) + wlf->dir[Y] * cos(wlf->calc->rot_speed);
		wlf->calc->old_plane = wlf->plane[X];
		wlf->plane[X] = wlf->plane[X] * cos(wlf->calc->rot_speed) - wlf->plane[Y] * sin(wlf->calc->rot_speed);
		wlf->plane[Y] = wlf->calc->old_plane * sin(wlf->calc->rot_speed) + wlf->plane[Y] * cos(wlf->calc->rot_speed);
	}
	if (key == 53)
		exit(0);
	draw(wlf, wlf->calc);
	return (0);
}