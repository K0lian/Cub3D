#include "cube3d.h"

void	text_set(char *str, t_data *data)
{
	int	id;

	id = -1;
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		id = 0;
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		id = 1;
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		id = 2;
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		id = 3;
	else if (str[0] == 'S' && str[1] == ' ')
		id = 4;
	else
		ft_say(3, "Wrong texture setting", data);
	str += 2;
	if (data->texture[id].ptr != NULL)
		ft_say(3, "Duplicated texture setting", data);
	while (*str == ' ')
		str++;
	text_form_set(str, &data->texture[id], data);
}

void	validate_set(t_data *data)
{
	if (data->color_ceil == -1U)
		ft_say(3, "Ceil color not found", data);
	if (data->color_floor == -1U)
		ft_say(3, "Floor color not found", data);
	if (data->texture[4].ptr == NULL)
		ft_say(3, "Sprite doesn't set", data);
	if (data->texture[3].ptr == NULL)
		ft_say(3, "E texture doesn't set", data);
	if (data->texture[2].ptr == NULL)
		ft_say(3, "W texture doesn't set", data);
	if (data->texture[1].ptr == NULL)
		ft_say(3, "S texture doesn't set", data);
	if (data->texture[0].ptr == NULL)
		ft_say(3, "N texture doesn't set", data);
	if (data->img.size_x == 0 || data->img.size_y == 0)
		ft_say(3, "Resolution doesn't set", data);
}

void	ft_parse_map(int id, char *len, t_data *data)
{
	unsigned int	ln_len;
	int				stt;
	int				i;

	i = 0;
	if (len)
		data->map.karta[i++] = len;
	data->map.size_x = ft_strlen(len);
	data->map.size_y = 1;
	stt = 1;
	while (stt >= 0 && *len != '\0')
	{
		stt = get_next_line(id, &len, data);
		ln_len = ytre(ln_len, len, data);
		data->map.karta[i] = len;
		chek_up_krt(i, data);
		i++;
	}
	if (stt == -1)
		ft_say(3, "Can't load map", data);
	if (stt != 0)
		ft_say(3, "Fucking lines are not allowed", data);
	setle_map(data);
}

void	ft_screne_parse(int id, char **len, t_data *data)
{
	int	status;

	status = 1;
	data->color_ceil = -1U;
	data->color_floor = -1U;
	while (status >= 0)
	{
		status = get_next_line(id, len, data);
		if (smol_chek(status, len, data, 1))
			res_set(*len, &data->img, data);
		else if (**len == 'C' && *(*len + 1) == ' ')
			colors_set(&data->color_ceil, *len, data);
		else if (**len == 'F' && *(*len + 1) == ' ')
			colors_set(&data->color_floor, *len, data);
		else if (**len == 'N' || **len == 'S' || **len == 'W' || **len == 'E')
			text_set(*len, data);
		else if (**len != '\0')
			return ;
		free(*len);
		if (status == 0)
			ft_say(3, "No map in file", data);
	}
	if (status == -1)
		ft_say(3, "Can't load map", data);
}

int	ft_parser(int as, char **av, t_data *data)
{
	char	*len;
	int		id;

	av++;
	if (ft_strlen(*av) < 5 || ft_memcmp(".cub", *av + ft_strlen(*av) - 4, 5))
		ft_say(2, "Nepavilnii filename", data);
	smol_chek(as, av, data, 0);
	id = open(*av, O_RDONLY);
	if (id == -1)
		ft_say(2, "Toje huinya", data);
	ft_screne_parse(id, &len, data);
	validate_set(data);
	ft_parse_map(id, len, data);
	if (rewd(as, av, id, data))
	{
		hgfd(1, data);
		return (1);
	}
	hgfd(0, data);
	return (0);
}
