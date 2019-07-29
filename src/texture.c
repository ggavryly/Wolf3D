/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 22:05:38 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/29 22:05:39 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		upload_texture(t_wlf *wlf,t_tex *tex, char *path)
{
	int 	w;
	int 	h;
	int 	tmp[3];

	w = TEXT_W;
	h = TEXT_H;
	if (!(tex->img = mlx_xpm_file_to_image(wlf->mlx, path, &w, &h)))
		exit_wlf(0);
	if (!(tex->texture = (int *)mlx_get_data_addr(tex->img, &tmp[0], &tmp[1], &tmp[2])))
		exit_wlf(0);
}

void		init_textures(t_wlf *wlf)
{
	wlf->textures = (t_tex *)malloc(sizeof(t_tex) * 8);

	upload_texture(wlf, &wlf->textures[0], "../textures/bluestone.xpm");
	upload_texture(wlf, &wlf->textures[1], "../textures/eagle.xpm");
	upload_texture(wlf, &wlf->textures[2], "../textures/redbrick.xpm");
	upload_texture(wlf, &wlf->textures[3], "../textures/greystone.xpm");
	upload_texture(wlf, &wlf->textures[4], "../textures/resizegena1.xpm");
	upload_texture(wlf, &wlf->textures[5], "../textures/resizegena2.xpm");
	upload_texture(wlf, &wlf->textures[6], "../textures/resizegena3.xpm");
	upload_texture(wlf, &wlf->textures[7], "../textures/resizegena4.xpm");
}
