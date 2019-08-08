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

void	key_down(t_wlf *wlf)
{
	if (wlf->wolf_map[(int)(wlf->pos[Y])]
	[(int)(wlf->pos[X] - wlf->dir[X] * wlf->calc->move_speed * 4)] == 0)
		wlf->pos[X] -= wlf->dir[X] * wlf->calc->move_speed;
	if (wlf->wolf_map[(int)(wlf->pos[Y] - wlf->dir[Y]
	* wlf->calc->move_speed * 4)][(int)(wlf->pos[X])] == 0)
		wlf->pos[Y] -= wlf->dir[Y] * wlf->calc->move_speed;
}

void	key_up(t_wlf *wlf)
{
	if (wlf->wolf_map[(int)(wlf->pos[Y])]
		[(int)(wlf->pos[X] + wlf->dir[X] * wlf->calc->move_speed * 4)] == 0)
		wlf->pos[X] += wlf->dir[X] * wlf->calc->move_speed;
	if (wlf->wolf_map[(int)(wlf->pos[Y] + wlf->dir[Y]
	* wlf->calc->move_speed * 4)][(int)(wlf->pos[X])] == 0)
		wlf->pos[Y] += wlf->dir[Y] * wlf->calc->move_speed;
}

void	key_right(t_wlf *w)
{
	w->calc->old_dir = w->dir[X];
	w->dir[X] = w->dir[X] * cos(-w->calc->rot_speed)
			- w->dir[Y] * sin(-w->calc->rot_speed);
	w->dir[Y] = w->calc->old_dir * sin(-w->calc->rot_speed)
			+ w->dir[Y] * cos(-w->calc->rot_speed);
	w->calc->old_plane = w->plane[X];
	w->plane[X] = w->plane[X] * cos(-w->calc->rot_speed)
			- w->plane[Y] * sin(-w->calc->rot_speed);
	w->plane[Y] = w->calc->old_plane * sin(-w->calc->rot_speed)
			+ w->plane[Y] * cos(-w->calc->rot_speed);
}

void	key_left(t_wlf *w)
{
	w->calc->old_dir = w->dir[X];
	w->dir[X] = w->dir[X] * cos(w->calc->rot_speed)
				- w->dir[Y] * sin(w->calc->rot_speed);
	w->dir[Y] = w->calc->old_dir * sin(w->calc->rot_speed)
				+ w->dir[Y] * cos(w->calc->rot_speed);
	w->calc->old_plane = w->plane[X];
	w->plane[X] = w->plane[X] * cos(w->calc->rot_speed)
			- w->plane[Y] * sin(w->calc->rot_speed);
	w->plane[Y] = w->calc->old_plane * sin(w->calc->rot_speed)
			+ w->plane[Y] * cos(w->calc->rot_speed);
}

int		key_press(int key, t_wlf *wlf)
{
	if (key == 53)
		exit_wlf(0);
	if (key == 17)
	{
		system("killall afplay &> /dev/null");
		if (!wlf->keys.t)
			system("afplay music/rick.mp3&");
		else
			system("afplay music/doors.mp3&");
		wlf->keys.t = (wlf->keys.t) ? (0) : (1);
	}
	if (key == KEY_A)
		wlf->keys.a = true;
	if (key == KEY_D)
		wlf->keys.d = true;
	if (key == KEY_W)
		wlf->keys.w = true;
	if (key == KEY_S)
		wlf->keys.s = true;
	if (key == SHIFT)
		wlf->keys.shift = true;
	return (0);
}
