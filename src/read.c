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

static int 	end_line(char *map, t_wlf *wlf)
{
	int 	i;
	int 	h;

	i = 0;
	h = 0;
	while (h < wlf->map_size[Y])
	{
		if (h == wlf->map_size[Y] - 1)
		{
			while (map[i])
			{
				if (map[i] != '1')
					return (-1);
				i++;
			}
			break;
		}
		if (map[i] == '\n')
		{
			h++;
			i++;
			continue;
		}
		i++;
	}
	return  (1);
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

void	allocate_map(char *map, t_wlf *wlf)
{
	int		i;
	int 	h;
	int 	w;

	i = 0;
	wlf->wolf_map = (int**)malloc(sizeof(int *) * wlf->map_size[Y]);
	while (i < wlf->map_size[Y])
	{
		wlf->wolf_map[i] = (int *)malloc(sizeof(int) * wlf->map_size[X]);
		i++;
	}
	i = 0;
	h = 0;
	w = 0;
	while (map[i])
	{
		if (map[i] == 'P')
			wlf->wolf_map[h][w] = 0;
		else if (map[i] == '1' || map[i] == '0')
			wlf->wolf_map[h][w] = (map[i] == '1') ? (1) : (0);
		if (map[i] == '\n')
		{
			i++;
			w = 0;
			h++;
			continue;
		}
		w++;
		i++;
	}
	free(map);
}

static int	analize_h(const char *line, t_wlf *wlf)
{
	int i;
	int h;
	int true_h;

	i = 0;
	h = 0;
	true_h = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != 'P' && line[i] != '0' && line[i] != '\n')
			return (-1);
		if (line[i] == '\n' && line[i - 1] == '1' && line[i + 1] == '1')
		{
			if (true_h == wlf->map_size[X])
			{
				h++;
				true_h = 0;
				i++;
				continue;
			}
			else
				return (-1);
		}
		else if (line[i] == '\n' && line[i - 1] != '1' && line[i + 1] != '1')
			return (-1);
		true_h++;
		i++;
	}
	if (true_h != wlf->map_size[X])
		return (-1);
	else if (true_h == wlf->map_size[X])
		h++;
	wlf->map_size[Y] = h;
	return (h);
}

int 		validate(char *map, t_wlf *wlf)
{
	int 	i;
	int 	h;
	int 	w;
	int 	start;

	i = 0;
	h = 0;
	w = 0;
	start = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			if (w == wlf->map_size[X])
			{
				h++;
				w = 0;
				i++;
				continue;
			}
		}
		if (map[i] == 'P' && map[i - 1] != '\n' && map[i + 1] != '\n'
		&& h > 0 && h < wlf->map_size[Y])
		{
			wlf->pos[Y] = h;
			wlf->pos[X] = w;
			start++;
		}
		i++;
		w++;
	}
	if (start != 1)
		return (-1);
	return (1);
}

void		read_map(t_wlf *wlf, char **av, int ar)
{
	char	*map;

	if (ar != 2)
	{
		ft_putstr("Usage: ./wolf3d [map_file]");
	}
	else
	{
		if (!(map = file_to_line(av[1])))
		{
			errno = 3;
			return;
		}
		else
		{
			analize_w(map, wlf);
			analize_h(map, wlf);
			if (wlf->map_size[X] == -1 || wlf->map_size[Y] == -1
			|| validate(map, wlf) == -1 || end_line(map, wlf) == -1)
			{
				free(map);
				ft_putstr("Invalid map");
				exit_wlf(0);
			}
			allocate_map(map, wlf);
		}
	}
}

