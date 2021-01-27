/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:19:02 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/25 17:19:02 by AleXwern         ###   ########.fr       */
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
		ft_splitfree(line);
	}
	close(conf);
}

int				main(void) //recv main
{
	int			conf;
	t_sender	sender;
	t_pack		package;

	conf = open("config.conf", O_RDONLY);
	if (conf == -1)
		error(FIL_ERROR);
	sender.ax = ax_init();
	get_config(conf, &sender);
	if (ax_resolvehost(&sender.ip, NULL, 9999))
		error(NET_ERROR);
	if (!(sender.server = ax_open(&sender.ip, sender.ax)))
		error(NET_ERROR);
	while (1)
	{
		if (!(sender.sock = ax_accept(sender.server, sender.ax)))
			continue;
		if (ax_recv(sender.sock, &package, sizeof(t_pack)) < (int)sizeof(t_pack))
			continue;
		//ft_printmem(&package, sizeof(t_pack));
		ft_putnbrln(package);
		get_filehead(&sender, package);
		sender.sock = ax_close(sender.sock);
		break;
	}
	return (0);
}