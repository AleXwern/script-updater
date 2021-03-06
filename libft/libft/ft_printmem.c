/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:00:08 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/26 15:06:20 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		gethex(t_uint8 num)
{
	char		*hex;

	hex = "0123456789abcdef";
	return (hex[num & 0xf]);
}

static char		*make_str(char *str, t_uint8 *cpy, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		t;

	i = 0;
	j = 0;
	while (i < len)
	{
		t = 0;
		while (t < WORDFT)
		{
			str[i + t] = gethex(cpy[j] >> 4);
			str[i + t + 1] = gethex(cpy[j]);
			j++;
			t += 2;
			if (t % WORDFT == 0)
				str[i + t] = '\n';
			if (t % WORDFT == WORDFT / 2)
				str[i + t] = ' ';
			if (t % WORDFT == 0 || t % WORDFT == WORDFT / 2)
				i++;
		}
		i += WORDFT;
	}
	return (str);
}

void			ft_printmem(const void *mem, size_t len)
{
	char		*str;
	t_uint8		*cpy;
	size_t		lbk;

	lbk = len / 8;
	str = (char*)ft_memalloc(sizeof(char) * len * 2 + lbk * 2 + 1);
	cpy = (t_uint8*)mem;
	str = make_str(str, cpy, len + lbk);
	str[len * 2 + lbk * 2] = '\0';
	ft_putstr("Printing out ");
	ft_putnbr(len);
	ft_putendl(" bytes of memory.");
	write(1, str, len * 2 + lbk * 2);
	free(str);
}
