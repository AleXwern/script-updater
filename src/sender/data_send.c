/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:55:13 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/26 13:55:13 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "updater.h"

char		**get_content(t_file *filelist, t_pack pack, char **files)
{
	char	str[DATA_PACK];
	size_t	i;
	int		fd;
	int		data;

	i = 0;
	while (i < pack)
	{
		fd = open(files[i], O_RDONLY);
		ft_putendl(files[i]);
		filelist[i].datalen = 0;
		while (1)
		{
			data = read(fd, str, DATA_PACK);
			if (data < 1)
				break;
			filelist[i].datalen += data;
		}
		i++;
	}
	return (NULL);
}

void		send_files(t_sender *sender, t_file *filelist, t_pack pack, char **files)
{
	char	content[DATA_PACK];
	size_t	i;
	size_t	sent;
	size_t	tosend;
	int		fd;

	get_content(filelist, pack, files);
	if (ax_send(sender->sock, &pack, sizeof(t_pack)) < (int)sizeof(t_pack))
		error(NET_ERROR);
	i = 0;
	while (i < pack)
	{
		if (ax_send(sender->sock, &filelist[i], sizeof(t_file)) < (int)sizeof(t_file))
			error(NET_ERROR);
		i++;
	}
	i = 0;
	while (i < pack)
	{
		if (ax_send(sender->sock, files[i], filelist[i].namelen) < (int)filelist[i].namelen)
			error(NET_ERROR);
		sent = 0;
		fd = open(files[i], O_RDONLY);
		ft_putnbrln(filelist[i].datalen);
		while (sent < filelist[i].datalen)
		{
			tosend = filelist[i].datalen - sent;
			if (tosend > DATA_PACK)
				tosend = DATA_PACK;
			read(fd, content, tosend);
			sent += ax_send(sender->sock, content, tosend);
		}
		i++;
	}
}