#include "cube3d.h"

int	move(int keycode, t_data *data)
{
	bzero(data->addr, data->img.size_x * data->img.size_y * 4);
	if (keycode == 53)
		ft_say(0, "Всего\nхоро\nшего", data);
	move_r_l(keycode, data);
	move_u_d_l_r(keycode, data);
	return (0);
}

int	jizn(t_data *data)
{
	int	color;
	int	x;
	int	y;

	y = 0;
	x = 0;
	color = 0;
	draw_walls(x, data);
	draw_sprites(color, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		ft_say(2, "HUI", &data);
	podgotovka(&data, ac, av);
	data.img.ptr = mlx_new_image(data.mlx, data.img.size_x, data.img.size_y);
	data.addr = mlx_get_data_addr(data.img.ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	game_init(&data);
	data.win = mlx_new_window(data.mlx, data.img.size_x, data.img.size_y,
			"Kolian's Cube");
	if (!data.win)
		ft_say(1, "Oshibka (mlx_new_window)", &data);
	while (data.n_pvrt--)
		move(RIGHT2, &data);
	jizn (&data);
	if (data.screen == 1)
		huyach_skrin(&data, av[2]);
	mlx_hook(data.win, 17, 1L <<17, q_exit, &data);
	mlx_key_hook(data.win, move, &data);
	mlx_loop_hook(data.mlx, jizn, &data);
	mlx_loop(data.mlx);
}
