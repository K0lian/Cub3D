#include "cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	q_exit(t_data *data)
{
	ft_say(0, NULL, data);
	return (0);
}

void	verLine(int x, int drawStart, int drawEnd, t_data *data)
{
	int	j;

	j = 0;
	while (j < drawStart)
	{
		my_mlx_pixel_put(data, x, j, data->color_floor);
		j++;
	}
	while (j <= drawEnd)
		j++;
	while (j < (int)data->img.size_y)
	{
		my_mlx_pixel_put(data, x, j, data->color_ceil);
		j++;
	}
}

void	sort_tex(t_data *data, int sprnum)
{
	t_sprite	tmp;

	tmp = (t_sprite){0, 0, 0};
	sttr(tmp, data, sprnum);
}

void	podgotovka(t_data *data, int ac, char **av)
{
	*data = (t_data){0};
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.45;
	data->rotSpeed = M_PI / 20;
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_say (1, "", data);
	data->screen = ft_parser(ac, av, data);
}
