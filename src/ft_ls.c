/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:01:24 by jjolivot          #+#    #+#             */
/*   Updated: 2018/09/01 20:22:56 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

struct s_pn	*ft_list_join(char *pathname, char *filename, struct s_pn *prev)
{
	struct s_pn *new;

	if (!(new = (t_pn *)malloc(sizeof(t_pn))))
		exit(0);
	if (prev)
		prev->next = new;
	new->prev = prev;
	new->filename = ft_strdup(filename);
	new->pathname = pathname;
	new->ext_print = ft_inspect_file(pathname, filename, &(new->modif_time));
	new->next = NULL;

	return (new);
}

void	ft_free_maillon(struct s_pn *maillon)
{
	free(maillon->ext_print);
	free(maillon->filename);
	free(maillon->pathname);
	free(maillon);
}

int	ft_check_permission(char *dirname)
{
	struct stat	*file;
	int			mod;
	int			ret;
	int			filetype;

	file = 0;
	if (!(file = (struct stat *)malloc(sizeof(struct stat))))
		exit(0);
	lstat(dirname, file);
	mod = ft_10_to_8(file->st_mode);
	mod = mod / 100;
	filetype = mod / 10;
	mod = mod % 10;
	ret = 2;
	if (mod != 4 || mod != 5 || mod != 6 || mod != 7)
		ret = 0;
	if (file->st_size == -4702111234474983746)
	{
		ft_putstr("./ft_ls: ");
		ft_putstr(dirname);
		ft_putstr(": No such file or directory\n");
		ret = 1;
	}
	free(file);
	return (ret);
}

struct s_pn	*ft_dir_to_list(char *dirname, char flags[5])
{
	DIR	*dir;
	struct dirent *dd;
	char *path;
	struct s_pn	*list;
	int			total_size;
	struct stat	*file;

	list = NULL;
	dir = opendir(dirname);
	total_size = 0;
	if (dir != NULL)
	{
		while ((dd = readdir(dir)))
		{
				printf("patate\n");
			if (dd && (dd->d_name[0] != '.' || flags[0] == 'a'))
			{
				path = ft_strjoin(dirname, "/");
				path = ft_f_strjoin(path, dd->d_name);
				list = ft_list_join(path, dd->d_name, list);
				if (!(file = (struct stat *)malloc(sizeof(struct stat))))
					exit(0);
				lstat(path, file);
				total_size = total_size + file->st_blocks;
				free(file);
			}
	printf("prout %i  %s\n", total_size, dd->d_name);
		}
		printf("fin\n");
		closedir(dir);
		while (list->prev)
			list = list->prev;
		list = ft_sort(list, flags);
		list->total_size = total_size;
	}
	else if (!ft_check_permission(dirname))
	{/*
		if (flags[1] != 'l')
			ft_putstr(dirname);
		else
			ft_putstr(ft_inspect_file(dirname, dirname, NULL));
			*/
		ft_putstr("ls: ");
		ft_putstr(dirname);
		ft_putstr(": Permission denied");
	}
	return (list);
}


void	ft_list_to_screen(struct s_pn *maillon, char *flags)
{
	struct s_pn *first;
	struct s_pn *tmp;

	first = maillon;
	while (maillon)
	{
		if (maillon->prev == NULL && flags[1] == 'l')
		{
			ft_putstr("total ");
			ft_putnbr(maillon->total_size);
			ft_putstr("\n");
		}
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
		tmp = maillon;
		maillon = maillon->next;
		if (flags[3] != 'R')
			ft_free_maillon(tmp);
			;
	}
	if (flags[3] == 'R')
	{
		maillon = first;
		while (maillon->next)
		{
			if (maillon->ext_print[0] == 'd' && ft_strcmp(maillon->filename, ".")
					&& ft_strcmp(maillon->filename, ".."))
			{
				ft_putstr(maillon->pathname);
				ft_putstr("\n\n");
				ft_ls(maillon->pathname, flags);
			}
			tmp = maillon;
			maillon = maillon->next;
			ft_free_maillon(tmp);
		}
	}

}

int	ft_ls(char *dirname, char *flags)
{
	struct s_pn *maillon;

	maillon = ft_dir_to_list(dirname, flags);
	if (maillon)
		ft_list_to_screen(maillon, flags);
	ft_putstr("\n");
	return (0);
}
