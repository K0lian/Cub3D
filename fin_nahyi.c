#include "cube3d.h"

int	ft_chek_simb(const char *s, int c)
{
	int		a;

	a = 0;
	if (s)
	{
		while (s[a])
		{
			if (s[a] == '9' || s[a] == '8' || s[a] == '7' || s[a] == '6'
				|| s[a] == '5' || s[a] == '4' || s[a] == '3' || s[a] == '2'
				|| s[a] == '1' || s[a] == '0' || s[a] == ' ' || s[a] == c)
				a++;
			else
				return (0);
		}
	}
	return (1);
}

void	res_set(const char *res_str, t_img *img, t_data *data)
{
	if (img->size_x)
		ft_say(3, "Duplicated Resolution setting", data);
	if (!ft_chek_simb(++res_str, 32))
		ft_say(3, "FUCK, there is some excess simbols", data);
	res_str = my_atoi(res_str, &img->size_x, UINT_MAX, data);
	if (res_str == NULL)
		ft_say(3, "Resolution X setting are suck", data);
	res_str = my_atoi(res_str, &img->size_y, UINT_MAX, data);
	if (*res_str != '\0' || img->size_x == 0 || img->size_y == 0)
		ft_say(3, "Wrong Resolution setting", data);
	if (res_str == NULL)
		ft_say(3, "Resolution Y setting are suck", data);
}
