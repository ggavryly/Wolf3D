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
# include <errno.h>
# include <mach/notify.h>
# include <stdbool.h>
# define X			0
# define Y			1
# define WIN_H		768
# define WIN_W		1280
# define TEXT_W		64
# define TEXT_H		64
# define SHIFT		257
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define START		0
# define END		1
# define GREY		0xD3D3D3

typedef struct		s_tex
{
	void			*img;
	int				*texture;
}					t_tex;

typedef struct		s_calc
{
	double			camera_x;
	double			ray_dir[2];
	double			side_dist[2];
	double			delta_dist[2];
	double			perl;
	double			move_speed;
	double			rot_speed;
	double			frame_time;
	double			old_dir;
	double			old_plane;
	double			wall_x;
	int				map[2];
	int				step[2];
	int				hit;
	int				side;
	int				line_h;
	int				draw[2];
	int				color;
	int				text_mode;
	int				tex[2];
	int				tmp;
}					t_calc;

typedef struct		s_keys
{
	bool			w;
	bool			s;
	bool			d;
	bool			a;
	bool			t;
	bool			shift;
}					t_keys;

typedef struct		s_wlf
{
	void			*mlx;
	void			*win;
	void			*img;
	double			pos[2];
	double			dir[2];
	double			plane[2];
	double			time;
	double			old_time;
	int				*buffer;
	int				**wolf_map;
	long long		map_size[2];
	int				tmp[3];
	t_calc			*calc;
	t_tex			*textures;
	t_keys			keys;
}					t_wlf;

typedef struct		s_val
{
	int				h;
	int				w;
	int				i;
	int				j;
}					t_val;

int					valid_name(char *map);
void				key_down(t_wlf *wlf);
void				key_up(t_wlf *wlf);
void				key_left(t_wlf *w);
void				key_right(t_wlf *w);
void				allocate_map(char *map, t_wlf *wlf);
int					analize_h(const char *line, t_wlf *wlf);
void				choose_sector_y(t_wlf *wlf, t_calc *calc);
void				fps_counter(t_wlf *wlf);
void				init_textures(t_wlf *wlf);
void				read_map(t_wlf *wlf, char **av, int ar);
int					exit_wlf(int code);
int					key_press(int key, t_wlf *wlf);
int					key_release(int key, t_wlf *wlf);
int					draw(t_wlf *wlf);
void				draw_vertical(int x, t_calc *calc, t_wlf *wlf, t_tex tex);
void				init_data(t_wlf *wlf, t_calc *calc);

#endif
