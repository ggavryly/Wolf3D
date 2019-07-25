/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:55:45 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/23 14:55:47 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/include/libft.h"
# include "/usr/local/include/mlx.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# define abs(x) ((x)<0 ? (-x) : (x));
# define X 0
# define Y 1
# define WIN_H		1000
# define WIN_W		1000
# define MAP_W		24
# define MAP_H		24
# define TEXT_W		64
# define TEXT_H		64
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define START 0
# define END 1
# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define WHITE		0xFFFFFF
# define YELLOW		0xFF00FF
# define GREY		0xD3D3D3
# define BLACK		0x000000

int worldMap[MAP_W][MAP_H];

typedef struct	s_calc
{
	double		camera_x;
	double		ray_dir[2];
	double		side_dist[2];
	double		delta_dist[2];
	double		perpwalldist;
	double		move_speed;
	double		rot_speed;
	double		frame_time;
	double		old_dir;
	double		old_plane;
	int			map[2];
	int 		step[2];
	int 		hit;
	int 		side;
	int 		line_h;
	int 		draw[2];
	int 		color;
}				t_calc;

typedef struct	s_wlf
{
	void		*mlx;
	void		*win;
	void		*img;
	double		pos[2];
	double		dir[2];
	double		plane[2];
	double		time;
	double		oldTime;
	int 		*buffer;
	int			**wolf_map;
	int 		tmp[3];
	t_calc		*calc;
}				t_wlf;

int 	key_event(int key, t_wlf *wlf);
void	draw(t_wlf *wlf, t_calc *calc);
void	init_data(t_wlf *wlf, t_calc *calc);

#endif
