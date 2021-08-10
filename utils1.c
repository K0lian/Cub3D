#include "cube3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	size_t	t;
	char	*p;

	p = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	t = 0;
	while (s1[t])
	{
		p[t] = s1[t];
		t++;
	}
	p[t] = '\0';
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cur;

	if (!dst && !src)
		return (NULL);
	cur = dst;
	while (n--)
		*cur++ = *(char *)src++;
	return (dst);
}
