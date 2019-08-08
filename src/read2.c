/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:38:54 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/30 15:38:55 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		analize_h2(t_val *v, t_wlf *wlf, const char *l)
{
	while (l[v->i])
	{
		if (l[v->i] != '1' && l[v->i] != 'P'
		&& l[v->i] != '0' && l[v->i] != '\n')
			return (-1);
		if (l[v->i] == '\n' && l[v->i - 1] == '1' && l[v->i + 1] == '1')
		{
			if (v->j == wlf->map_size[X])
			{
				v->h++;
				v->j = 0;
				v->i++;
				continue;
			}
			else
				return (-1);
		}
		else if (l[v->i] == '\n' && l[v->i - 1] != '1' && l[v->i + 1] != '1')
			return (-1);
		v->j++;
		v->i++;
	}
	return (1);
}

int		analize_h(const char *line, t_wlf *wlf)
{
	t_val	val;

	val.i = 0;
	val.h = 0;
	val.j = 0;
	if (analize_h2(&val, wlf, line) == -1)
		return (-1);
	if (val.j != wlf->map_size[X])
		return (-1);
	else if (val.j == wlf->map_size[X])
		val.h++;
	wlf->map_size[Y] = val.h;
	return (val.h);
}

void	allocate_map2(t_val *val, t_wlf *wlf)
{
	val->i = 0;
	wlf->wolf_map = (int**)malloc(sizeof(int *) * wlf->map_size[Y]);
	while (val->i < wlf->map_size[Y])
	{
		wlf->wolf_map[val->i] = (int *)malloc(sizeof(int) * wlf->map_size[X]);
		val->i++;
	}
	val->i = 0;
	val->h = 0;
	val->w = 0;
}

void	allocate_map(char *map, t_wlf *wlf)
{
	t_val val;

	allocate_map2(&val, wlf);
	while (map[val.i])
	{
		if (map[val.i] == 'P')
			wlf->wolf_map[val.h][val.w] = 0;
		else if (map[val.i] == '1' || map[val.i] == '0')
			wlf->wolf_map[val.h][val.w] = (map[val.i] == '1') ? (1) : (0);
		if (map[val.i] == '\n')
		{
			val.i++;
			val.w = 0;
			val.h++;
			continue;
		}
		val.w++;
		val.i++;
	}
	free(map);
}

int		valid_name(char *map)
{
	int		i;
	char	*str;

	if (!map)
		return (1);
	i = 0;
	while (map[i])
		i++;
	str = (map + (i - 4));
	if (ft_strcmp(str, ".wlf"))
		return (-1);
	return (0);
}
