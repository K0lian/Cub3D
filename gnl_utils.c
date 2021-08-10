#include "cube3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	j;
	unsigned int	k;
	char			*sj;

	if ((!s1) || (!s2))
		return (NULL);
	k = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	sj = (char *)(malloc(sizeof(char) * (k + j + 1)));
	if (!(sj))
		return (NULL);
	k = -1;
	while (s1[++k] != '\0')
		sj[k] = s1[k];
	j = -1;
	while (s2[++j] != '\0')
		sj[k + j] = s2[j];
	sj[j + k] = '\0';
	free((void *)s1);
	return (sj);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*su;

	i = 0;
	if (!s)
		return (NULL);
	su = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!(su))
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		su[i] = '\0';
		return (su);
	}
	while (i < len)
	{
		su[i] = s[start + i];
		i++;
	}
	su[i] = '\0';
	return (su);
}

int	ft_strchrr(char *str)
{
	int		i;
	char	c;

	c = '\n';
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
