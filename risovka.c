#include "cube3d.h"

void	prorisovka_sten(int x, double k, t_data *data)
{
	int	y;
	int	texY;

	y = data->drawStart;
	while (y < data->drawEnd)
	{
		texY = (int)data->texPos & (TEXHEIGHT - 1);
		data->texPos += data->step;
		if (data->side == 0 && data->rayDirX > 0)
			data->color = *(unsigned int *)(data->texture[0].addr + (texY
						* data->texture[0].line_length + data->texX * 4));
		else if (data->side == 0 && data->rayDirX < 0)
			data->color = *(unsigned int *)(data->texture[1].addr + (texY
						*data->texture[1].line_length + data->texX * 4));
		else if (data->side == 1 && data->rayDirY > 0)
			data->color = *(unsigned int *)(data->texture[2].addr + (texY
						* data->texture[2].line_length + data->texX * 4));
		else
			data->color = *(unsigned int *)(data->texture[3].addr + (texY
						* data->texture[3].line_length + data->texX * 4));
		my_mlx_pixel_put(data, x, y, data->color);
		y++;
	}
	data->ZBuffer[x] = k;
	verLine(x, data->drawStart, data->drawEnd, data);
}

void	draw_walls(int x, t_data *data)
{
	double	*perpWallDist;

	perpWallDist = (double *)malloc(sizeof(double) * data->img.size_x);
	if (!perpWallDist)
		ft_say(2, "Fucking malloc error", data);
	while (x < (int)data->img.size_x)
	{
		rasschet_start(x, data);
		rasschet_raydir(data);
		rasschet_hit(data);
		if (data->side == 0)
			perpWallDist[x] = (data->mapX - data->posX + (1 - data->stepX)
					/ 2) / data->rayDirX;
		else
			perpWallDist[x] = (data->mapY - data->posY + (1 - data->stepY)
					/ 2) / data->rayDirY;
		data->lineHeight = (int)(data->img.size_y / perpWallDist[x]);
		rasschet_draw(perpWallDist[x], data);
		prorisovka_sten(x, perpWallDist[x], data);
		x++;
	}
	free(perpWallDist);
}

void	rasschet_spr(int i, t_data *data)
{
	data->spriteX = data->sprite[i].x - data->posX;
	data->spriteY = data->sprite[i].y - data->posY;
	data->invDet = 1.0 / (data->planeX * data->dirY - data->dirX
			* data->planeY);
	data->transformX = data->invDet * (data->dirY * data->spriteX
			- data->dirX * data->spriteY);
	data->transformY = data->invDet * (-data->planeY * data->spriteX
			+ data->planeX * data->spriteY);
	data->sprite[i].distance = data->transformY;
	data->spriteScreenX = (int)((data->img.size_x / 2) * (1 + data->transformX
				/ data->transformY));
	data->spriteHeight = abs((int)(data->img.size_y / data->transformY));
	data->drawStartY = data->img.size_y / 2 - data->spriteHeight / 2;
	if (data->drawStartY < 0)
		data->drawStartY = 0;
	data->drawEndY = data->spriteHeight / 2 + data->img.size_y / 2;
	if (data->drawEndY >= (int)data->img.size_y)
		data->drawEndY = (int)data->img.size_y - 1;
	data->spriteWidth = abs((int)(data->img.size_y / (data->transformY)));
	data->drawStartX = data->spriteScreenX - data->spriteWidth / 2;
	if (data->drawStartX < 0)
		data->drawStartX = 0;
	data->drawEndX = data->spriteWidth / 2 + data->spriteScreenX;
	if (data->drawEndX >= (int)data->img.size_x)
		data->drawEndX = (int)data->img.size_x - 1;
}

void	ft_risyem(int texX, int color, int sprX, t_data *data)
{
	int	r;
	int	d;
	int	texY;

	if (data->transformY > 0 && sprX > 0 && sprX < (int)data->img.size_x
		&& data->ZBuffer[sprX] > data->transformY)
	{
		r = data->drawStartY;
		while (r < data->drawEndY)
		{
			d = r * 256 - data->img.size_y * 128 + data->spriteHeight * 128;
			texY = ((d * TEXWIGTH) / data->spriteHeight) / 256;
			color = *(unsigned int *)(data->texture[4].addr + (texY
						* data->texture[4].line_length + texX * 4));
			if (color >> 24 == 0)
				my_mlx_pixel_put(data, sprX, r, color);
			r++;
		}
	}
}

void	draw_sprites(int color, t_data *data)
{
	int	sprX;
	int	texX;
	int	i;

	i = 0;
	sort_tex(data, data->numsprites);
	while (i < data->numsprites)
	{
		rasschet_spr(i, data);
		sprX = data->drawStartX;
		while (sprX < data->drawEndX)
		{
			texX = (int)(256 * (sprX - (data->spriteScreenX
							- data->spriteWidth / 2)) * TEXWIGTH
					/ data->spriteWidth) / 256;
			ft_risyem(texX, color, sprX, data);
			sprX++;
		}
		i++;
	}
}
