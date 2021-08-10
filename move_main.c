#include "cube3d.h"

void	f_left(double oldDirX, double oldPlaneX, t_data *data)
{
	data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY
		* sin(-data->rotSpeed);
	data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY
		* cos(-data->rotSpeed);
	data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY
		* sin(-data->rotSpeed);
	data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY
		* cos(-data->rotSpeed);
}

void	f_rite(double oldDirX, double oldPlaneX, t_data *data)
{
	data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY
		* sin(data->rotSpeed);
	data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY
		* cos(data->rotSpeed);
	data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY
		* sin(data->rotSpeed);
	data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY
		* cos(data->rotSpeed);
}

void	move_r_l(int keycode, t_data *data)
{
	double	oldPlaneX;
	double	oldDirX;

	oldPlaneX = data->planeX;
	oldDirX = data->dirX;
	if (keycode == LEFT2)
	{
		f_left(oldDirX, oldPlaneX, data);
	}
	if (keycode == RIGHT2)
	{
		f_rite(oldDirX, oldPlaneX, data);
	}
}

void	move_horizontal(int keycode, t_data *data)
{
	if (keycode == RIGHT)
	{
		if (data->map.karta[(int)data->posY][(int)(data->posX + data->planeX
			* data->moveSpeed)] != 49)
			data->posX += data->planeX * data->moveSpeed;
		if (data->map.karta[(int)(data->posY + data->planeY
				* data->moveSpeed)][(int)data->posX] != 49)
			data->posY += data->planeY * data->moveSpeed;
	}
	if (keycode == LEFT)
	{
		if (data->map.karta[(int)data->posY][(int)(data->posX - data->planeX
			* data->moveSpeed)] != 49)
			data->posX -= data->planeX * data->moveSpeed;
		if (data->map.karta[(int)(data->posY - data->planeY
				* data->moveSpeed)][(int)data->posX] != 49)
			data->posY -= data->planeY * data->moveSpeed;
	}
}

void	move_u_d_l_r(int keycode, t_data *data)
{
	if (keycode == UP || keycode == 126)
	{
		if (data->map.karta[(int)data->posY][(int)(data->posX + data->dirX
			* data->moveSpeed)] != 49)
			data->posX += data->dirX * data->moveSpeed;
		if (data->map.karta[(int)(data->posY + data->dirY * data->moveSpeed)]
			[(int)data->posX] != 49)
			data->posY += data->dirY * data->moveSpeed;
	}
	if (keycode == DOWN || keycode == 125)
	{
		if (data->map.karta[(int)(data->posY)][(int)(data->posX - data->dirX
			* data->moveSpeed)] != 49)
			data->posX -= data->dirX * data->moveSpeed;
		if (data->map.karta[(int)(data->posY - data->dirY * data->moveSpeed)]
			[(int)(data->posX)] != 49)
			data->posY -= data->dirY * data->moveSpeed;
	}
	move_horizontal(keycode, data);
}
