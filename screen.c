#include "cube3d.h"

static void	ft_color_to_bmp(t_data *data)
{
	int	j;
	int	i;

	i = data->img.size_y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < (int)data->img.size_x)
		{
			data->bmp.clr = *(int *)(data->addr + (data->line_length * i + j
						* 4));
			write(data->bmp.fd, &data->bmp.clr, 4);
			j++;
		}
		i--;
	}
}

char	*ft_strnstr(const char *str, const char *ne, size_t len)
{
	size_t	q;
	size_t	w;
	size_t	e;

	q = -1;
	if (!*ne)
		return ((char *)str);
	while (++q < len && *(str + q))
	{
		w = 0;
		e = 0;
		if (*(str + q + w) == *(ne + w))
		{
			while (q + w < len + 1 && *(str + q + w) && *(ne + w))
			{
				if (*(str + q + w) != *(ne + w))
					break ;
				w++;
				e++;
			}
			if (e == ft_strlen(ne))
				return ((char *)str + q);
		}
	}
	return (NULL);
}

static void	ft_head_bmp(t_data *data)
{
	data->bmp.h2 = 40;
	data->bmp.offset = 54;
	data->bmp.size = data->bmp.offset + ((data->img.size_x * 3) + \
	(data->img.size_x % 4)) * data->img.size_y;
	data->bmp.head[0] = (unsigned char) 'B';
	data->bmp.head[1] = (unsigned char) 'M';
	data->bmp.head[2] = (unsigned char)data->bmp.size;
	data->bmp.head[3] = (unsigned char)(data->bmp.size >> 8);
	data->bmp.head[4] = (unsigned char)(data->bmp.size >> 16);
	data->bmp.head[5] = (unsigned char)(data->bmp.size >> 24);
	data->bmp.head[10] = (unsigned char)(data->bmp.offset);
	data->bmp.head[14] = (unsigned char)(data->bmp.h2);
	data->bmp.head[18] = (unsigned char)data->img.size_x;
	data->bmp.head[19] = (unsigned char)(data->img.size_x >> 8);
	data->bmp.head[20] = (unsigned char)(data->img.size_x >> 16);
	data->bmp.head[21] = (unsigned char)(data->img.size_x >> 24);
	data->bmp.head[22] = (unsigned char)data->img.size_y;
	data->bmp.head[23] = (unsigned char)(data->img.size_y >> 8);
	data->bmp.head[24] = (unsigned char)(data->img.size_y >> 16);
	data->bmp.head[25] = (unsigned char)(data->img.size_y >> 24);
	data->bmp.head[26] = (unsigned char)(1);
	data->bmp.head[28] = (unsigned char)(32);
	write(data->bmp.fd, data->bmp.head, 54);
	ft_color_to_bmp(data);
}

void	huyach_skrin(t_data *data, char *av)
{
	data->bmp.head = ft_calloc(54, sizeof(char));
	if (ft_strlen(av) != 6)
		ft_say(2, "bmp died\nPres F to pay respect", data);
	else
	{
		if (ft_strnstr(av, "--save", 6))
		{
			data->bmp.fd = open("bmp.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
			ft_head_bmp(data);
			close(data->bmp.fd);
			ft_say(0, "bmp gotov", data);
		}
	}
}
