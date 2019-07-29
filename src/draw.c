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

void	choose_sector(t_wlf *wlf, t_calc *calc)
{
	if (calc->ray_dir[X] < 0)
	{
		calc->step[X] = -1;
		calc->side_dist[X] = (wlf->pos[X] - calc->map[X]) * calc->delta_dist[X];
	}
	else
	{
		calc->step[X] = 1;
		calc->side_dist[X] = (calc->map[X] + 1.0 - wlf->pos[X]) * calc->delta_dist[X];
	}
	if (calc->ray_dir[Y] < 0)
	{
		calc->step[Y] = -1;
		calc->side_dist[Y] = (wlf->pos[Y] - calc->map[Y]) * calc->delta_dist[Y];
	}
	else
	{
		calc->step[Y] = 1;
		calc->side_dist[Y] = (calc->map[Y] + 1.0 - wlf->pos[Y]) * calc->delta_dist[Y];
	}
}

void	choose_color(t_wlf *wlf, t_calc *calc)
{
	calc->line_h = (int)(WIN_H / calc->perpwalldist);
	calc->draw[START] = -calc->line_h / 2 + WIN_H / 2;
	if (calc->draw[START] < 0)
		calc->draw[START] = 0;
	calc->draw[END] = calc->line_h / 2 + WIN_H / 2;
	if (calc->draw[END] >= WIN_H)
		calc->draw[END] = WIN_H - 1;
	calc->text_mode = (calc->text_select) ? (4) : (0);
	if (((calc->ray_dir[X] < 0 && calc->ray_dir[Y]< 0)
		 || (calc->ray_dir[X] >= 0 && calc->ray_dir[Y]< 0)) && calc->side == 1)
		calc->text_mode = (calc->text_select) ? (5) : (1);
	if (((calc->ray_dir[X] < 0 && calc->ray_dir[Y]>= 0)
		 || (calc->ray_dir[X] >= 0 && calc->ray_dir[Y]>= 0)) && calc->side == 1)
		calc->text_mode = (calc->text_select) ? (6) : (2);
	if (((calc->ray_dir[X] >= 0 && calc->ray_dir[Y]< 0)
		 || (calc->ray_dir[X] >= 0 && calc->ray_dir[Y]>= 0)) && calc->side == 0)
		calc->text_mode =(calc->text_select) ? (7) : (3);
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
	calc->perpwalldist = 0;
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
			calc->side_dist[Y] +=  calc->delta_dist[Y];
			calc->map[Y] += calc->step[Y];
			calc->side = 1;
		}
		if (wlf->wolf_map[calc->map[Y]][calc->map[X]] > 0)
			calc->hit = 1;
	}
}

int		draw(t_wlf *wlf)
{
	int		x;

	x = 0;
	while(x < WIN_W)
	{
		pre_calc(wlf, wlf->calc, x);
		choose_sector(wlf, wlf->calc);
		ray_run(wlf, wlf->calc);
		if (wlf->calc->side == 0)
			wlf->calc->perpwalldist = (wlf->calc->map[X]- wlf->pos[X] + (double )(1 - wlf->calc->step[X]) / 2) / wlf->calc->ray_dir[X];
		else
			wlf->calc->perpwalldist = (wlf->calc->map[Y] - wlf->pos[Y] + (double)(1 - wlf->calc->step[Y]) / 2) / wlf->calc->ray_dir[Y];
		choose_color(wlf, wlf->calc);
		draw_vertical(x, wlf->calc, wlf, wlf->textures[wlf->calc->text_mode]);
		x++;
	}
	wlf->oldTime = wlf->time;
	wlf->time = clock();
	wlf->calc->frame_time = (wlf->time - wlf->oldTime) / 100.0;
	wlf->calc->move_speed = 0.10;
	wlf->calc->rot_speed = 0.05;
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img, 0, 0);
	mlx_string_put(wlf->mlx, wlf->win, 5, 5, 0x000000, "FPS: ");
	char *str = ft_itoa((int)wlf->calc->frame_time);
	mlx_string_put(wlf->mlx, wlf->win, 50, 5, 0x000000, str);
	free(str);
	return (0);
}
