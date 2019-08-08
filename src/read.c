/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:44:17 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/28 15:44:19 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	end_line(const char *map, t_wlf *wlf)
{
	t_val val;

	val.i = 0;
	val.h = 0;
	while (val.h < wlf->map_size[Y])
	{
		if (val.h == wlf->map_size[Y] - 1)
		{
			while (map[val.i])
			{
				if (map[val.i] != '1')
					return (-1);
				val.i++;
			}
			break ;
		}
		if (map[val.i] == '\n')
		{
			val.h++;
			val.i++;
			continue ;
		}
		val.i++;
	}
	return (1);
}

static int	analize_w(const char *line, t_wlf *wlf)
{
	int i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		if (line[i] != '1')
			return (-1);
		i++;
	}
	wlf->map_size[X] = i;
	return (i);
}

void		validate2(const char *map, t_wlf *wlf, t_val *val)
{
	if (map[val->i] == 'P' && map[val->i - 1] != '\n' && map[val->i + 1] != '\n'
		&& val->h > 0 && val->h < wlf->map_size[Y])
	{
		wlf->pos[Y] = val->h;
		wlf->pos[X] = val->w;
		val->j++;
	}
}

int			validate(char *map, t_wlf *wlf)
{
	t_val	val;

	val.i = 0;
	val.h = 0;
	val.w = 0;
	val.j = 0;
	while (map[val.i])
	{
		if (map[val.i] == '\n')
		{
			if (val.w == wlf->map_size[X])
			{
				val.h++;
				val.w = 0;
				val.i++;
				continue;
			}
		}
		validate2(map, wlf, &val);
		val.i++;
		val.w++;
	}
	if (val.j != 1)
		return (-1);
	return (1);
}

void		read_map(t_wlf *wlf, char **av, int ar)
{
	char	*map;

	if (ar != 2 || !ft_strnstr(av[0], "./wolf3d", 8) || valid_name(av[1]))
		exit_wlf(2);
	else
	{
		if (!(map = file_to_line(av[1])))
			exit_wlf(1);
		else
		{
			analize_w(map, wlf);
			analize_h(map, wlf);
			if (wlf->map_size[X] == -1 || wlf->map_size[Y] == -1
			|| validate(map, wlf) == -1 || end_line(map, wlf) == -1 ||
			wlf->map_size[X] > 250 || wlf->map_size[Y] > 250)
			{
				free(map);
				exit_wlf(3);
			}
			allocate_map(map, wlf);
			system("afplay music/doors.mp3&");
		}
	}
}
