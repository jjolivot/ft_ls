/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:01:24 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/26 02:13:44 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

struct s_pn	*ft_list_join(char *pathname, char *filename, struct s_pn *prev)
{
	struct s_pn *new;

	new = (t_pn *)malloc(sizeof(t_pn));
	if (prev)
		prev->next = new;
	new->prev = prev;
	new->filename = filename;
	new->pathname = pathname;
	new->ext_print = ft_inspect_file(pathname, filename, &(new->modif_time));
	new->next = NULL;

	return (new);
}


struct s_pn	*ft_dir_to_list(char *dirname, char flags[5])
{
	DIR	*dir;
	struct dirent *dd;
	char *path;
	struct s_pn *list;

	list = NULL;
	dir = opendir(dirname);
	while ((dd = readdir(dir)))
	{
		if (dd->d_name[0] != '.' || flags[0] == 'a')
		{
			path = ft_strjoin(dirname, "/");
			path = ft_f_strjoin(path, dd->d_name);
			list = ft_list_join(path, dd->d_name, list);
		}
	}
	closedir(dir);
	return (list);
}


void	ft_list_to_screen(struct s_pn *maillon, char *flags)
{
	while (maillon->prev)
		maillon = maillon->prev;
	if (flags[4] == 't')
		maillon = ft_sort(maillon, flags);
	while (maillon)
	{
		if (flags[1] == 'l')
		{
			ft_putstr(maillon->ext_print);
			ft_putstr("\n");
		}
		else
		{
			ft_putstr(maillon->filename);
			ft_putstr("\n");
		}
		if (flags[3] != 'R')
			//ft_free maillon
			;
		maillon = maillon->next;
	}
	if (flags[3] == 'R')
	{
		while (maillon->prev != NULL)
			maillon = maillon->prev;
		while (maillon->next)
		{
			if (maillon->ext_print[0] == 'd')
			{
				ft_putstr(maillon->pathname);
				ft_putstr("\n\n");
				ft_ls(maillon->pathname, flags);
			}
			// ft_free maillon
			maillon = maillon->next;
		}
	}

}

int	ft_ls(char *dirname, char *flags)
{
	struct s_pn *maillon;

	maillon = ft_dir_to_list(dirname, flags);
	ft_list_to_screen(maillon, flags);
	ft_putstr("\n");
	return (0);
}
