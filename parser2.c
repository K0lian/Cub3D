#include "cube3d.h"

void	setle_map(t_data *data)
{
	unsigned int	line_len;
	unsigned int	i;
	char			*line;

	line = NULL;
	i = 0;
	while (i < data->map.size_y)
	{
		line = (data->map.karta)[i];
		(data->map.karta)[i] = NULL;
		(data->map.karta)[i] = (char *)malloc(data->map.size_x);
		if (data->map.karta[i] == NULL)
			ft_say(4, "Set map (MAF)", data);
		line_len = ft_strlen(line);
		ft_memcpy(data->map.karta[i], line, line_len);
		ft_memset(data->map.karta[i] + line_len, ' ',
			data->map.size_x - line_len);
		free(line);
		i++;
	}
	proc_set_map(data);
	if (data->posX == 0)
		ft_say(3, "Where is igrok???", data);
}

char	*my_atoi(const char *src_str, unsigned long long *dsi, unsigned long
		max, t_data *data)
{
	unsigned long	num;

	while (*src_str == ' ')
		src_str++;
	if (*src_str == ',')
		ft_say(3, "FUCK, 2 or more ',' in the row", data);
	if (ft_isdigit(*src_str) == 0)
		ft_say(3, "Hueta a ne color", data);
	num = 0;
	while (ft_isdigit(*src_str))
	{
		num = num * 10 + *src_str++ - '0';
		if (num > UINT_MAX)
			while (ft_isdigit(*src_str))
				src_str++;
		else if (max != UINT_MAX && num > max)
			ft_say(3, "255+ content", data);
	}
	if (num > UINT_MAX)
		*dsi = UINT_MAX;
	else
		*dsi = num;
	while (*src_str == ' ')
		src_str++;
	return ((char *)src_str);
}

const char	*colors_set1(unsigned int *trg, const char *scolor,
		unsigned long long *Rd, t_data *data)
{
	if (*trg != (unsigned) -1)
		ft_say(3, "Duplicated F or C color setting", data);
	scolor++;
	scolor = my_atoi(scolor, Rd, 255, data);
	if (*scolor++ != ',')
		ft_say(3, "'F R,G,B'/'C R,G,B'\nOh, that hurts", data);
	if (scolor == NULL)
		ft_say(3, "Fucking Red-", data);
	if (!ft_chek_simb(scolor, 44))
		ft_say(3, "FUCK, there is some excess color simbols", data);
	if (*scolor == ',')
		ft_say(3, "FUCK, 2 or more ',' in the row", data);
	return (scolor);
}

void	colors_set(unsigned int *trg, const char *scolor, t_data *data)
{
	unsigned long long	U;
	unsigned long long	Gr;
	unsigned long long	Rd;

	Rd = 0;
	scolor = colors_set1(trg, scolor, &Rd, data);
	scolor = my_atoi(scolor, &Gr, 255, data);
	if (*scolor++ != ',')
		ft_say(3, "'F R,G,B'/'C R,G,B'\nOh, that hurts", data);
	if (scolor == NULL)
		ft_say(3, "Fucking Green-", data);
	if (*scolor == ',')
		ft_say(3, "FUCK, 2 or more ',' in the row", data);
	scolor = my_atoi(scolor, &U, 255, data);
	if (*scolor != '\0')
		ft_say(3, "Fucking line redundant symbols", data);
	if (scolor == NULL)
		ft_say(3, "Fucking Blue-", data);
	*trg = (Rd << 16) | (Gr << 8) | U;
}

void	text_form_set(char *str, t_img *texture, t_data *data)
{
	size_t	lnstr;

	lnstr = ft_strlen(str);
	if (lnstr < 5)
		ft_say(2, "Texture format sucks", data);
	if (ft_memcmp(".xpm", str + lnstr - 4, 5) == 0)
	{
		texture->ptr = mlx_xpm_file_to_image(data->mlx, str,
				(int *)&texture->size_x, (int *)&texture->size_y);
		if (!texture->ptr)
			ft_say(3, "Can't load texture", data);
	}
	else
		ft_say(2, "Texture format sucks", data);
	texture->addr = (unsigned int *)mlx_get_data_addr(texture->ptr,
			&data->bits_per_pixel, &texture->line_length, &data->endian);
}
