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
	if (key == KEY_UP)
	{
		if(wlf->wolf_map[(int)(wlf->pos[Y])][(int)(wlf->pos[X] + wlf->dir[X] * wlf->calc->move_speed)] == 0)
			wlf->pos[X] += wlf->dir[X] * wlf->calc->move_speed;
		if(wlf->wolf_map[(int)(wlf->pos[Y] + wlf->dir[Y] * wlf->calc->move_speed)][(int)(wlf->pos[X])] == 0)
			wlf->pos[Y] += wlf->dir[Y] * wlf->calc->move_speed;
	}
	if (key == KEY_DOWN)
	{
		if(wlf->wolf_map[ (int)(wlf->pos[Y])][(int)(wlf->pos[X] - wlf->dir[X] * wlf->calc->move_speed)] == 0)
			wlf->pos[X] -= wlf->dir[X] * wlf->calc->move_speed;
		if(wlf->wolf_map[(int)(wlf->pos[Y] - wlf->dir[Y] * wlf->calc->move_speed)][ (int)(wlf->pos[X])] == 0)
			wlf->pos[Y] -= wlf->dir[Y] * wlf->calc->move_speed;
	}
	if (key == KEY_RIGHT)
	{
		wlf->calc->old_dir = wlf->dir[X];
		wlf->dir[X] = wlf->dir[X] * cos(-wlf->calc->rot_speed) - wlf->dir[Y] * sin(-wlf->calc->rot_speed);
		wlf->dir[Y] = wlf->calc->old_dir * sin(-wlf->calc->rot_speed) + wlf->dir[Y] * cos(-wlf->calc->rot_speed);
		wlf->calc->old_plane = wlf->plane[X];
		wlf->plane[X] = wlf->plane[X] * cos(-wlf->calc->rot_speed) - wlf->plane[Y] * sin(-wlf->calc->rot_speed);
		wlf->plane[Y] = wlf->calc->old_plane * sin(-wlf->calc->rot_speed) + wlf->plane[Y] * cos(-wlf->calc->rot_speed);
	}
	if (key == KEY_LEFT)
	{
		wlf->calc->old_dir = wlf->dir[X];
		wlf->dir[X] = wlf->dir[X] * cos(wlf->calc->rot_speed) - wlf->dir[Y] * sin(wlf->calc->rot_speed);
		wlf->dir[Y] = wlf->calc->old_dir * sin(wlf->calc->rot_speed) + wlf->dir[Y] * cos(wlf->calc->rot_speed);
		wlf->calc->old_plane = wlf->plane[X];
		wlf->plane[X] = wlf->plane[X] * cos(wlf->calc->rot_speed) - wlf->plane[Y] * sin(wlf->calc->rot_speed);
		wlf->plane[Y] = wlf->calc->old_plane * sin(wlf->calc->rot_speed) + wlf->plane[Y] * cos(wlf->calc->rot_speed);
	}
	if (key == 53)
	{
		system("leaks Wolf3D");
		exit_wlf(0);
	}
	if (key == 17)
		wlf->calc->text_select = (wlf->calc->text_select) ? (0) : (1);
	draw(wlf);
	return (0);
}