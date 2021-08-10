#include "cube3d.h"

void	rasschet_raydir(t_data *data)
{
	if (data->rayDirX < 0)
	{
		data->stepX = -1;
		data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;
	}
	else
	{
		data->stepX = 1;
		data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
	}
	if (data->rayDirY < 0)
	{
		data->stepY = -1;
		data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
	}
	else
	{
		data->stepY = 1;
		data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
	}
}

void	rasschet_hit(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->sideDistX <= data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->mapX += data->stepX;
			data->side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			data->side = 1;
		}
		if (data->map.karta[data->mapY][data->mapX] == 49)
			hit = 1;
	}
}

void	rasschet_start(int x, t_data *data)
{
	data->cameraX = 2 * x / (double)(data->img.size_x) - 1;
	data->rayDirX = data->dirX + data->planeX * data->cameraX;
	data->rayDirY = data->dirY + data->planeY * data->cameraX;
	data->mapX = (int)(data->posX);
	data->mapY = (int)(data->posY);
	data->deltaDistX = sqrt(1 + (data->rayDirY * data->rayDirY)
			/ (data->rayDirX * data->rayDirX));
	data->deltaDistY = sqrt(1 + (data->rayDirX * data->rayDirX)
			/ (data->rayDirY * data->rayDirY));
}

void	rasschet_draw(double k, t_data *data)
{
	data->drawStart = -data->lineHeight / 2 + data->img.size_y / 2;
	if (data->drawStart < 0)
		data->drawStart = 0;
	data->drawEnd = data->lineHeight / 2 + data->img.size_y / 2;
	if (data->drawEnd >= (int)data->img.size_y)
		data->drawEnd = data->img.size_y - 1;
	if (data->side == 0)
		data->wallX = data->posY + k * data->rayDirY;
	else
		data->wallX = data->posX + k * data->rayDirX;
	data->wallX -= floor((data->wallX));
	data->texX = (int)(data->wallX * (double)TEXWIGTH);
	if (data->side == 0 && data->rayDirX > 0)
		data->texX = TEXWIGTH - data->texX - 1;
	if (data->side == 1 && data->rayDirY < 0)
		data->texX = TEXWIGTH - data->texX - 1;
	data->step = 1.0 * TEXHEIGHT / data->lineHeight;
	data->texPos = (data->drawStart - data->img.size_y / 2 + data->lineHeight
			/ 2) * data->step;
}
