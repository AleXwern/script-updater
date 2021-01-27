/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updater.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:07:41 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/22 14:07:41 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATER_H
# define UPDATER_H

#include "libft.h"
#include "libax.h"
#include "get_next_line.h"
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

#include <stdio.h>

//Number of bytes sent/received per transmission when transmitting files.
//Never ever change this value!!
#define DATA_PACK	200
#define FILENAME	50

typedef size_t	t_pack;

typedef struct	s_file
{
	size_t		namelen;
	size_t		datalen;
}				t_file;

typedef struct	s_sender
{
	t_libax		*ax;
	t_ip		ip;
	t_socket	*sock;
	t_socket	*server;
	char		*version;
}				t_sender;

//errors
#define	DEFAULT		"No errors"
#define FIL_ERROR	"Error while trying to handle file!"
#define NET_ERROR	"Error while trying to establish a connection!\nThere may be a maintenance."
#define REC_ERROR	"Error while trying to receive data!"
#define SND_ERROR	"Error while trying to send data!"
#define MEM_ERROR	"No heap data left on system!"

void			error(char *msg);

void		get_filehead(t_sender *sender, t_pack pack);
void		receive_files(t_sender *sender, t_file *file, t_pack pack);

t_file		*get_filelist(t_pack *pack, char ***filelist);
void		send_files(t_sender *sender, t_file *filelist, t_pack pack, char **files);

#endif