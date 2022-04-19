/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:03:47 by jkarosas          #+#    #+#             */
/*   Updated: 2022/04/14 01:13:18 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	negative;
	int	sum;
	int	i;

	i = 0;
	negative = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative = -1;
		i++;
	}
	sum = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	if (negative < 0)
		sum = sum * -1;
	return (sum);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != 0)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

size_t	ft_length(int n)
{
	size_t	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	len;
	long	num;

	len = ft_length(n);
	a = (char *)malloc(len + 1);
	if (a == NULL)
		return (NULL);
	num = n;
	if (n < 0)
	{
		num = -num;
		a[0] = '-';
	}
	if (num == 0)
		a[0] = '0';
	a[len] = '\0';
	while (num != 0)
	{
		a[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (a);
}
