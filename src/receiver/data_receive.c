/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_receive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:08:44 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/26 13:08:44 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "updater.h"

void		receive_files(t_sender *sender, t_file *file, t_pack pack)
{
	size_t	i;
	int		fd;
	char	*name;
	size_t	haveread;
	size_t	toread;
	char	str[DATA_PACK];

	i = 0;
	while (i < pack)
	{
		ft_putstr("Name: ");
		ft_putnbrln(file[i].namelen);
		if (!(name = (char*)malloc(file[i].namelen)))
			error(MEM_ERROR);
		if (ax_recv(sender->sock, name, file[i].namelen) != (int)file[i].namelen)
			error(REC_ERROR);
		ft_putendl(name);
		fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 00777);
		free(name);
		haveread = 0;
		while (haveread < file[i].datalen)
		{
			toread = file[i].datalen - haveread;
			if (toread > DATA_PACK)
				toread = DATA_PACK;
			if (ax_recv(sender->sock, str, toread) != (int)toread)
				error(REC_ERROR);
			write(fd, str, toread);
			haveread += toread;
		}
		close(fd);
		i++;
	}
}

void		get_filehead(t_sender *sender, t_pack pack)
{
	t_file	*file;
	size_t	i;

	ft_putstr("Files: ");
	ft_putnbrln(pack);
	if (!(file = (t_file*)malloc(sizeof(t_file) * pack)))
		error(MEM_ERROR);
	i = 0;
	while (i < pack)
	{
		if (ax_recv(sender->sock, &file[i], sizeof(t_file)) < (int)sizeof(t_file))
			error(REC_ERROR);
		printf("Files: %ld %ld\n", file[i].namelen, file[i].datalen);
		i++;
	}
	receive_files(sender, file, pack);
}