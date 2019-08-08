/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:02:55 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/28 19:02:57 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fps_counter(t_wlf *wlf)
{
	char	*str;

	wlf->old_time = wlf->time;
	wlf->time = clock();
	wlf->calc->frame_time = (wlf->time - wlf->old_time) / 100.0;
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img, 0, 0);
	mlx_string_put(wlf->mlx, wlf->win, 5, 5, 0x000000, "FPS: ");
	str = ft_itoa((int)wlf->calc->frame_time);
	mlx_string_put(wlf->mlx, wlf->win, 50, 5, 0x000000, str);
	free(str);
}

void	choose_sector_y(t_wlf *w, t_calc *c)
{
	if (c->ray_dir[Y] < 0)
	{
		c->step[Y] = -1;
		c->side_dist[Y] = (w->pos[Y] - c->map[Y]) * c->delta_dist[Y];
	}
	else
	{
		c->step[Y] = 1;
		c->side_dist[Y] = (c->map[Y] + 1.0 - w->pos[Y]) * c->delta_dist[Y];
	}
}

void	cycle(t_wlf *wlf, t_calc *calc)
{
	if (calc->side == 0)
		calc->wall_x = wlf->pos[Y] + calc->perl * calc->ray_dir[Y];
	else
		calc->wall_x = wlf->pos[X] + calc->perl * calc->ray_dir[X];
	calc->wall_x -= floor(calc->wall_x);
	calc->tex[X] = (int)(calc->wall_x * (double)TEXT_W);
	if (calc->side == 0 && calc->ray_dir[X] > 0)
		calc->tex[X] = TEXT_W - calc->tex[X] - 1;
	if (calc->side == 1 && calc->ray_dir[Y] < 0)
		calc->tex[X] = TEXT_W - calc->tex[X] - 1;
}

void	draw_vertical(int x, t_calc *calc, t_wlf *wlf, t_tex tex)
{
	int	i;
	int b;

	i = 0;
	b = 0;
	cycle(wlf, calc);
	while (i < WIN_H)
	{
		calc->tmp = i * 256 - WIN_H * 128 + calc->line_h * 128;
		calc->tex[Y] = ((calc->tmp * TEXT_W) / calc->line_h) / 256;
		calc->color = tex.texture[TEXT_W * calc->tex[Y] + calc->tex[X]];
		if (i <= calc->draw[START])
			wlf->buffer[i * WIN_W + x] = 0x99E1FF;
		else if (i >= calc->draw[START] && i < calc->draw[END])
			wlf->buffer[i * WIN_W + x] = calc->color;
		else
		{
			wlf->buffer[i * WIN_W + x] = GREY;
			b++;
		}
		i++;
	}
}
