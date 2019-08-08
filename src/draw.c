/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:04:54 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/24 17:04:55 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	choose_sector(t_wlf *wlf, t_calc *cl)
{
	if (cl->ray_dir[X] < 0)
	{
		cl->step[X] = -1;
		cl->side_dist[X] = (wlf->pos[X] - cl->map[X]) * cl->delta_dist[X];
	}
	else
	{
		cl->step[X] = 1;
		cl->side_dist[X] = (cl->map[X] + 1.0 - wlf->pos[X]) * cl->delta_dist[X];
	}
	choose_sector_y(wlf, cl);
}

void	choose_color(t_calc *calc, t_wlf *wlf)
{
	calc->line_h = (int)(WIN_H / calc->perl);
	calc->draw[START] = -calc->line_h / 2 + WIN_H / 2;
	if (calc->draw[START] < 0)
		calc->draw[START] = 0;
	calc->draw[END] = calc->line_h / 2 + WIN_H / 2;
	if (calc->draw[END] >= WIN_H)
		calc->draw[END] = WIN_H - 1;
	calc->text_mode = (wlf->keys.t) ? (4) : (0);
	if (((calc->ray_dir[X] < 0 && calc->ray_dir[Y] < 0)
	|| (calc->ray_dir[X] >= 0 && calc->ray_dir[Y] < 0)) && calc->side == 1)
		calc->text_mode = (wlf->keys.t) ? (5) : (1);
	if (((calc->ray_dir[X] < 0 && calc->ray_dir[Y] >= 0)
	|| (calc->ray_dir[X] >= 0 && calc->ray_dir[Y] >= 0)) && calc->side == 1)
		calc->text_mode = (wlf->keys.t) ? (6) : (2);
	if (((calc->ray_dir[X] >= 0 && calc->ray_dir[Y] < 0)
	|| (calc->ray_dir[X] >= 0 && calc->ray_dir[Y] >= 0)) && calc->side == 0)
		calc->text_mode = (wlf->keys.t) ? (7) : (3);
}

void	pre_calc(t_wlf *wlf, t_calc *calc, int x)
{
	calc->camera_x = 2 * x / (double)(WIN_W) - 1;
	calc->ray_dir[X] = wlf->dir[X] + wlf->plane[X] * calc->camera_x;
	calc->ray_dir[Y] = wlf->dir[Y] + wlf->plane[Y] * calc->camera_x;
	calc->map[X] = (int)(wlf->pos[X]);
	calc->map[Y] = (int)(wlf->pos[Y]);
	calc->side_dist[X] = 0;
	calc->side_dist[Y] = 0;
	calc->delta_dist[X] = fabs(1 / calc->ray_dir[X]);
	calc->delta_dist[Y] = fabs(1 / calc->ray_dir[Y]);
	calc->perl = 0;
	calc->step[X] = 0;
	calc->step[Y] = 0;
	calc->hit = 0;
	calc->side = 0;
}

void	ray_run(t_wlf *wlf, t_calc *calc)
{
	while (calc->hit == 0)
	{
		if (calc->side_dist[X] < calc->side_dist[Y])
		{
			calc->side_dist[X] += calc->delta_dist[X];
			calc->map[X] += calc->step[X];
			calc->side = 0;
		}
		else
		{
			calc->side_dist[Y] += calc->delta_dist[Y];
			calc->map[Y] += calc->step[Y];
			calc->side = 1;
		}
		if (wlf->wolf_map[calc->map[Y]][calc->map[X]] > 0)
			calc->hit = 1;
	}
}

int		draw(t_wlf *w)
{
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		pre_calc(w, w->calc, x);
		choose_sector(w, w->calc);
		ray_run(w, w->calc);
		if (w->calc->side == 0)
			w->calc->perl = (w->calc->map[X] - w->pos[X] +
					(double)(1 - w->calc->step[X]) / 2) / w->calc->ray_dir[X];
		else
			w->calc->perl = (w->calc->map[Y] - w->pos[Y] +
					(double)(1 - w->calc->step[Y]) / 2) / w->calc->ray_dir[Y];
		choose_color(w->calc, w);
		draw_vertical(x, w->calc, w, w->textures[w->calc->text_mode]);
		x++;
	}
	fps_counter(w);
	return (0);
}
