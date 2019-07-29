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

void	draw_vertical(int x, t_calc *calc, t_wlf *wlf, t_tex tex)
{
	int	i;
	int b;
	double wallX;

	i = 0;
	b = 0;
	if (calc->side == 0)
		wallX = wlf->pos[Y] + calc->perpwalldist * calc->ray_dir[Y];
	else
		wallX = wlf->pos[X] + calc->perpwalldist * calc->ray_dir[X];
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)TEXT_W);
	if (calc->side == 0 && calc->ray_dir[X] > 0)
		texX = TEXT_W - texX - 1;
	if (calc->side == 1 && calc->ray_dir[Y] < 0)
		texX = TEXT_W - texX - 1;
	while (i < WIN_H)
	{
		int d = i * 256 - WIN_H * 128 + calc->line_h * 128;
		int texY = ((d * TEXT_W) / calc->line_h) / 256;
		calc->color = tex.texture[TEXT_W * texY + texX];
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
