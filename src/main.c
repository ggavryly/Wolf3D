/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:16:55 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/30 15:16:57 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	move(t_wlf *wlf)
{
	if (wlf->keys.w)
		key_up(wlf);
	else if (wlf->keys.s)
		key_down(wlf);
}

void	sprint(t_wlf *wlf)
{
	if (wlf->keys.shift)
		wlf->calc->move_speed = (wlf->calc->move_speed <= 0.2) ? (0.2) : (0.1);
	else if (!wlf->keys.shift)
		wlf->calc->move_speed = (wlf->calc->move_speed >= 0.1) ? (0.1) : (0.2);
}

void	rotate(t_wlf *wlf)
{
	if (wlf->keys.d)
		key_right(wlf);
	else if (wlf->keys.a)
		key_left(wlf);
}

int		draw_me(t_wlf *wlf)
{
	if (wlf->keys.a || wlf->keys.d)
		rotate(wlf);
	if (wlf->keys.s || wlf->keys.w)
		move(wlf);
	sprint(wlf);
	draw(wlf);
	return (0);
}

int		main(int ar, char **av)
{
	t_calc		calc;
	t_wlf		wlf;

	read_map(&wlf, av, ar);
	init_data(&wlf, &calc);
	init_textures(&wlf);
	mlx_hook(wlf.win, 2, 0, key_press, &wlf);
	mlx_hook(wlf.win, 3, 0, key_release, &wlf);
	mlx_hook(wlf.win, 17, 0, exit_wlf, NULL);
	mlx_loop_hook(wlf.mlx, draw_me, (void *)&wlf);
	mlx_loop(wlf.mlx);
	return (0);
}
