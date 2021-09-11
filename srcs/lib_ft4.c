#include "main.h"

char	*ft_searchinstr(const char *s, int c)
{
	unsigned long long		i;

	if (!s)
		return (NULL);
	i = 0;
	while (1)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		else if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}

static int	intlen(long n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	put_int(char *s, long n, int neg, int len)
{
	s[len--] = '\0';
	if (n == 0)
	{
		s[0] = '0';
		return ;
	}
	if (neg == -1)
		s[0] = '-';
	while (n > 0)
	{
		s[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	long	nn;
	int		len;
	int		neg;
	char	*ret;

	neg = 1;
	nn = (long)n;
	len = 0;
	if (nn < 0)
	{
		nn *= -1;
		neg *= -1;
		len++;
	}
	len += intlen(nn);
	if (n == 0)
		len = 1;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	put_int(ret, nn, neg, len);
	return (ret);
}

int	ft_atoi(char *s)
{
	int		ret;
	int		i;
	int		neg;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == '\v')
		i++;
	neg = 1;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		neg = -neg;
		i++;
	}
	ret = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = ret * 10 + s[i] - '0';
		i++;
	}
	return (ret * neg);
}
