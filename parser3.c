#include "cube3d.h"

void	hgfd(int screenshot, t_data *data)
{
	if (screenshot == 1)
	{
		if (data->img.size_y > 1440)
			data->img.size_y = 1440;
		if (data->img.size_x > 2560)
			data->img.size_x = 2560;
	}
	else
	{
		if (data->img.size_y > 1440)
			data->img.size_y = 1440;
		if (data->img.size_x > 2560)
			data->img.size_x = 2560;
	}
	if (data->img.size_x < 2)
		data->img.size_x = 2;
}

void	yntf(t_data *data)
{
	int	n;

	data->colum = malloc(sizeof(struct s_column *) * data->img.size_x);
	if (!data->colum)
		ft_say(4, "Ray columns (MAF)", data);
	n = 0;
	while (n < (int)data->img.size_x)
	{
		data->colum[n] = ft_calloc(1, sizeof(struct s_column));
		if (data->colum[n] == NULL)
			ft_say(4, "Column (MAF)", data);
		n++;
	}
}

void	game_init(t_data *data)
{
	t_sprite	max_res;

	max_res = (t_sprite){0, 0, 0};
	yntf(data);
}

void	proc_set_map(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	data->numsprites = -1;
	while (y < data->map.size_y)
	{
		x = 0;
		while (x < data->map.size_x)
		{
			chek_map(data->map.karta, x, y, data);
			if (data->map.karta[y][x] == '2')
			{
				if (++data->numsprites >= 2048)
					ft_say(2, "To many sprites", data);
				data->sprite[data->numsprites]
					= (t_sprite){x + 0.5, y + 0.5, 0};
			}
			x++;
		}
		y++;
	}
	++data->numsprites;
}
