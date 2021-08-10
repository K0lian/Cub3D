#include "cube3d.h"

void	sttr(t_sprite tmp, t_data *data, int sprnum)
{
	int	j;
	int	d;

	j = 0;
	while (j < sprnum)
	{
		d = j;
		while (d < sprnum)
		{
			if (data->sprite[j].distance < data->sprite[d].distance)
			{
				tmp = data->sprite[j];
				data->sprite[j] = data->sprite[d];
				data->sprite[d] = tmp;
			}
			d++;
		}
		j++;
	}
}

void	chek_up_krt(int i, t_data *data)
{
	int	j;

	if (i == MAXLEN)
		ft_say(4, "File to long", data);
	j = 0;
	while (data->map.karta[0][j])
	{
		if (data->map.karta[0][j] == 49 || data->map.karta[0][j] == 32)
			j++;
		else
			ft_say(4, "Huevaya karta (1st stroka)", data);
	}
}
