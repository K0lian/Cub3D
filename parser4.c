#include "cube3d.h"

void	term_put(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	free_say(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (data->colum)
	{
		while (i < data->img.size_x)
			free(data->colum[i++]);
		free(data->colum);
	}
	i = 0;
	if (*data->map.karta)
	{
		while (i < data->map.size_x)
			free(data->map.karta[i++]);
	}
	i = 0;
	while (i < sizeof(data->texture) / sizeof(t_img))
	{
		if (data->texture[i].ptr)
			mlx_destroy_image(data->mlx, data->texture[i].ptr);
		i++;
	}
}

int	ft_say(int return_value, char *message, t_data *data)
{
	if (return_value)
	{
		if (return_value)
			term_put("Error", 2);
		term_put(message, 2);
		if (return_value == 5)
			term_put("Unable to save screenshot\n", 2);
		if (return_value == 1)
			term_put("Crash MLX/X11\n", 2);
		if (return_value == 2)
			term_put("Usage: ./cub3D scene_name.cub [--save]\n", 2);
		if (return_value == 3)
			term_put("Fix scene file to make it work\n", 2);
	}
	free_say(data);
	if (return_value)
		free(data->mlx);
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit (return_value);
}
