/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 15:42:00 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/22 22:49:05 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include "ft_ls.h"
#include <stdio.h>

struct s_pn	*ft_list_join(char *pathname, char *filename, struct s_pn *prev)
{
	struct s_pn *new;

	new = (t_pn *)malloc(sizeof(t_pn));
	if (prev)
		prev->next = new;
	new->prev = prev;
	new->filename = filename;
	new->pathname = pathname;
	new->next = NULL;

	return (new);
}


struct s_pn	*ft_dir_to_list(char *dirname)
{
	DIR	*dir;
	struct dirent *dd;
	char *path;
	struct s_pn *list;

	//list = (struct s_pn *)malloc(sizeof(t_pn));
	//list->prev = NULL;
	list = NULL;
	dir = opendir(dirname);
	while ((dd = readdir(dir)))
	{
		if (dd->d_name[0] != '.')
		{
			path = ft_strjoin(dirname, "/");
			path = ft_f_strjoin(path, dd->d_name);
			list = ft_list_join(path, dd->d_name, list);
		}
	}
	closedir(dir);
	return (list);
}

int	ft_list_to_screen(struct s_pn *list, char flag)
{
	if (flag == 'r')
	{
//		list = list->prev;
		while (list)
		{
			free(list->next);
			ft_inspect_file(list->pathname, list->filename);
			ft_putstr("\n");
			free(list->pathname);
			list = list->prev;
		}
	}
	else
	{
		while (list->prev != NULL)
			list = list->prev;
		while (list)
		{
			free(list->prev);
			ft_inspect_file(list->pathname, list->filename);
			ft_putstr("\n");
			free(list->pathname);
			list = list->next;
		}
	}
	return (0);
}

int	ft_ls(char *dirname, char flag)
{
	struct s_pn *list;
	DIR			*dir;
	struct dirent	*dd;
	struct	stat *file;
	char	*path;

	list = ft_dir_to_list(dirname);
	if (list != NULL)
		ft_list_to_screen(list, flag);
	if (flag == 'R')
	{
		dir = opendir(dirname);
		while ((dd = readdir(dir)))
		{
			file = (struct stat *)malloc(sizeof(struct stat));
			path = ft_strjoin(dirname, "/");
			path = ft_f_strjoin(path, dd->d_name);
			stat(path, file);
//			ft_putnbr(ft_10_to_8(file->st_mode));
//			printf("\n");
			if (ft_10_to_8(file->st_mode) / 10000 == 4 && ft_strcmp(dd->d_name, ".")
					&& ft_strcmp(dd->d_name, ".."))
			{
				ft_putstr(path);
				ft_putstr("\n");
				ft_ls(path, 'R');
			}
			free(path);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
//	struct s_pn *list;

	argc = 1;
	ft_ls(argv[1], argv[2][0]);
//	list = ft_dir_to_list(argv[1]);
//	ft_list_to_screen(list, argv[2][0]);
	while (1);
	return (0);
}
