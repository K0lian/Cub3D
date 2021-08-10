#include "cube3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	e;

	e = 0;
	while (e < len)
		((unsigned char *)b)[e++] = c;
	return (b);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*on;
	const unsigned char	*to;

	if (n == 0)
		return (0);
	on = (const unsigned char *)s1;
	to = (const unsigned char *)s2;
	while (n--)
	{
		if (*on != *to)
			return (*on - *to);
		on++;
		to++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p)
		ft_memset(p, 0, count * size);
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	char	k;
	int		a;

	a = 0;
	k = c;
	while (s[a])
	{
		if (s[a] == k)
			return ((char *)&s[a]);
		a++;
	}
	if (c == 0)
		return ((char *)&s[a]);
	return (0);
}
