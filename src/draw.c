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

#include "../include/wolf3d.h"

void	draw_vertical(int x, t_calc *calc, t_wlf *wlf)
{
	int	i;
	int b;

	i = 0;
	b = 0;
	while (i < WIN_H)
	{
		if (i <= calc->draw[START])
			wlf->buffer[i * WIN_W + x] = BLACK;
		else if (i >= calc->draw[START] && i <= calc->draw[END])
			wlf->buffer[i * WIN_W + x] = calc->color;
		else
		{
			wlf->buffer[i * WIN_W + x] = GREY;
			b++;
		}
		i++;
	}
}

void 	draw(t_wlf *wlf, t_calc *calc)
{
	ft_bzero(wlf->buffer, WIN_H * WIN_W * (sizeof(int)));
	for(int x = 0; x < WIN_W; x++)
	{
		//calculate ray position and direction
		calc->camera_x = 2 * x / (double)(WIN_W) - 1; //x-coordinate in camera space
		calc->ray_dir[X] = wlf->dir[X] + wlf->plane[X] * calc->camera_x;
		calc->ray_dir[Y] = wlf->dir[Y] + wlf->plane[Y] * calc->camera_x;
		//which box of the map we're in
		calc->map[X] = (int)(wlf->pos[X]);
		calc->map[Y] = (int)(wlf->pos[Y]);

		//length of ray from current position to next x or y-side
		calc->side_dist[X] = 0;
		calc->side_dist[Y] = 0;

		//length of ray from one x or y-side to next x or y-side
		calc->delta_dist[X] = fabs(1 / calc->ray_dir[X]);
		calc->delta_dist[Y] = fabs(1 / calc->ray_dir[Y]);
		calc->perpwalldist = 0;

		//what direction to step in x or y-direction (either +1 or -1)
		calc->step[X] = 0;
		calc->step[Y] = 0;

		calc->hit = 0; //was there a wall hit?
		calc->side = 0; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
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
		//perform DDA
		while (calc->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
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
			//Check if ray has hit a wall
			if (worldMap[calc->map[X]][calc->map[Y]] > 0)
				calc->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (calc->side == 0)
			calc->perpwalldist = (calc->map[X]- wlf->pos[X] + (double )(1 - calc->step[X]) / 2) / calc->ray_dir[X];
		else
			calc->perpwalldist = (calc->map[Y] - wlf->pos[Y] + (double)(1 - calc->step[Y]) / 2) / calc->ray_dir[Y];

		//Calculate height of line to draw on screen
		calc->line_h = (int)(WIN_H / calc->perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		calc->draw[START] = -calc->line_h / 2 + WIN_H / 2;
		if (calc->draw[START] < 0)
			calc->draw[START] = 0;
		calc->draw[END] = calc->line_h / 2 + WIN_H / 2;
		if (calc->draw[END] >= WIN_H)
			calc->draw[END] = WIN_H - 1;



		//texturing calculations

		//choose wall color
		if (worldMap[calc->map[X]][calc->map[Y]] == 1)
			calc->color = RED;
		else if (worldMap[calc->map[X]][calc->map[Y]] == 2)
			calc->color = GREEN;
		else if (worldMap[calc->map[X]][calc->map[Y]] == 3)
			calc->color = BLUE;
		else if (worldMap[calc->map[X]][calc->map[Y]] == 4)
			calc->color = WHITE;
		else
			calc->color = YELLOW;
		//give x and y sides different brightness
		if (calc->side == 1)
			calc->color = calc->color / 2;
		draw_vertical(x, calc, wlf);
	}
	//timing for input and FPS counter
	wlf->oldTime = wlf->time;
	wlf->time = clock();
	calc->frame_time = (wlf->time - wlf->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	// FPS counter

	//speed modifiers
	calc->move_speed = 0.10; //the constant value is in squares/second
	calc->rot_speed = 0.10; //the constant value is in radians/second
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img, 0, 0);
}
