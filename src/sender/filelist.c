/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:56:55 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/26 13:56:55 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "updater.h"

t_file		*get_filelist(t_pack *pack, char ***filelist)
{
	char	*dummy;
	char	str[DATA_PACK];
	int		fd;
	t_file	*files;
	size_t	i;

	fd = open("filelist.conf", O_RDONLY);
	ft_bzero(str, FILENAME);
	dummy = ft_strnew(1);
	while (read(fd, str, FILENAME) > 0)
	{
		dummy = ft_strfjoin(dummy, str);
		ft_bzero(str, FILENAME);
	}
	close(fd);
	*filelist = ft_strsplit(dummy, '\n');
	free(dummy);
	*pack = ft_listlen(*filelist);
	ft_printmem(*filelist, (*pack + 1) * sizeof(char*));
	files = (t_file*)malloc(sizeof(t_file) * (*pack));
	i = 0;
	ft_putnbrln(*pack);
	while (i < *pack)
	{
		ft_putendl((*filelist)[i]);
		files[i].namelen = ft_strlen((*filelist)[i]);
		if ((*filelist)[i][files[i].namelen - 1] == 0xD)
			(*filelist)[i][files[i].namelen - 1] = '\0';
		i++;
	}
	return (files);
}