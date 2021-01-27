/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:59:47 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/21 15:18:10 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifdef __cplusplus
extern "C" {
#endif

# include "libft.h"
# define BUFF_SIZE 32
# define MAX_FD 8192

int get_next_line(const int fd, char **line);

#ifdef __cplusplus
}
#endif

#endif
