#include "../include/wolf3d.h"

int main(int ar, char **av)
{
	t_calc		calc;
	t_wlf		wlf;

	read_map(&wlf, av, ar);
	init_data(&wlf, &calc);
	init_textures(&wlf);
	draw(&wlf);
	mlx_hook(wlf.win, 2, 0, key_event, &wlf);
	mlx_hook(wlf.win, 17, 0, exit_wlf, NULL);
	mlx_loop_hook(wlf.mlx, draw, (void *)&wlf);
	mlx_loop(wlf.mlx);
}