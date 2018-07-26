/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 23:14:49 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/25 20:05:41 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include "libft/libft.h"
#include <stdio.h>

typedef struct	s_pn
{
	struct s_pn	*prev;
	char	*pathname;
	char	*filename;
	char	*ext_print;
	char	filetype;
	time_t	modif_time;
	struct s_pn	*next;
}				t_pn;

struct s_pn	*ft_sort(struct s_pn *maillon, char *flags);
int			ft_ls(char *dirname, char flags[5]);
char		*ft_inspect_file(char *filepath, char *filename, time_t *modif_time);

#endif
