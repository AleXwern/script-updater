/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:59:10 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/22 12:59:10 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "updater.h"

void			error(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void			get_config(int conf, t_sender *sender)
{
	char	*dummy;
	char	**line;

	while (get_next_line(conf, &dummy) > 0)
	{
		line = ft_strsplit(dummy, ' ');
		free(dummy);
		if (!ft_strcmp(line[0], "version:"))
			sender->version = ft_strdup(line[1]);
		else if (!ft_strcmp(line[0], "server:"))
			ax_resolvehost(&sender->ip, line[1], 9999);
		ft_splitfree(line);
	}
	close(conf);
}

int				main(void) //sender main
{
	int			conf;
	t_sender	sender;
	t_file		*filelist;
	t_pack		pack;
	char		**files;

	conf = open("config.conf", O_RDONLY);
	if (conf == -1)
		error(FIL_ERROR);
	sender.ax = ax_init();
	get_config(conf, &sender);
	if (!(sender.sock = ax_open(&sender.ip, sender.ax)))
		error(NET_ERROR);
	pack = 0;
	files = NULL;
	filelist = get_filelist(&pack, &files);
	send_files(&sender, filelist, pack, files);
	ax_close(sender.sock);
	return (0);
}