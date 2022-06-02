/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:01 by shima             #+#    #+#             */
/*   Updated: 2022/06/02 11:14:33 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	chose_fmt(char c, va_list *ap, int *len, size_t *i);
int		put_u_nb_base(size_t nb, char *base, char c);
int		put_nb(int nb);
void	put_str(va_list *ap, int *output_len);

__attribute__((format(printf, 1, 2)))	int	ft_printf(const char *fmt, ...)
{
	int		len;
	size_t	i;
	va_list	ap;

	len = 0;
	i = 0;
	va_start(ap, fmt);
	errno = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
			chose_fmt(fmt[i + 1], &ap, &len, &i);
		else
			len += write(STDOUT_FILENO, &fmt[i++], 1);
		if (errno != 0)
			break ;
	}
	va_end(ap);
	return (len);
}

void	chose_fmt(char c, va_list *ap, int *len, size_t *i)
{
	char	_c;

	if (c == 'c')
	{
		_c = va_arg(*ap, int);
		*len += write(STDOUT_FILENO, &_c, 1);
	}
	else if (c == 's')
		put_str(ap, len);
	else if (c == 'p')
		*len += put_u_nb_base(va_arg(*ap, size_t), "0123456789abcdef", c);
	else if (c == 'd' || c == 'i')
		*len += put_nb(va_arg(*ap, int));
	else if (c == 'u')
		*len += put_u_nb_base(va_arg(*ap, unsigned int), "0123456789", c);
	else if (c == 'x')
		*len += put_u_nb_base(va_arg(*ap, unsigned int), "0123456789abcdef", c);
	else if (c == 'X')
		*len += put_u_nb_base(va_arg(*ap, unsigned int), "0123456789ABCDEF", c);
	else if (c == '%')
		*len += write(STDOUT_FILENO, "%", 1);
	if (c == '\0')
		(*i)++;
	else
		(*i) += 2;
}

int	put_u_nb_base(size_t nb, char *base, char c)
{
	int		addition;
	size_t	base_len;
	size_t	i;
	char	result[14];

	addition = 0;
	if (c == 'p')
	{
		addition = 2;
		write(STDOUT_FILENO, "0x", 2);
	}
	base_len = ft_strlen(base);
	i = 0;
	if (nb == 0)
		return (write(STDOUT_FILENO, "0", 1) + addition);
	while (nb != 0)
	{
		result[13 - i++] = base[nb % base_len];
		nb /= base_len;
	}
	return (write(STDOUT_FILENO, &result[13 - i + 1], i) + addition);
}

int	put_nb(int nb)
{
	char	result[11];
	size_t	i;

	i = 0;
	if (nb == 0)
		return (write(STDOUT_FILENO, "0", 1));
	else if (nb > 0)
	{
		while (nb != 0)
		{
			result[10 - i++] = '0' + (nb % 10);
			nb /= 10;
		}
	}
	else
	{
		while (nb != 0)
		{
			result[10 - i++] = '0' - (nb % 10);
			nb /= 10;
		}
		result[10 - i++] = '-';
	}
	return (write(STDOUT_FILENO, &result[10 - i + 1], i));
}

void	put_str(va_list *ap, int *output_len)
{
	size_t		len;
	const char	*s;

	s = va_arg(*ap, const char *);
	if (!s)
	{
		*output_len += write(STDOUT_FILENO, "(null)", 6);
		return ;
	}
	len = ft_strlen(s);
	*output_len += write(STDOUT_FILENO, s, len);
}
