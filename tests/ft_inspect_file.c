/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:09:05 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/22 22:49:12 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <grp.h>
#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include "libft/libft.h"


int		ft_power(int nbr, int power)
{
	int base;

	base = nbr;
	while (--power > 0)
		nbr = nbr * base;
	return(nbr);
}

char	ft_file_type(int mod)
{
	mod = mod / 10;
	if (mod == 6)
		return ('b');
	if (mod == 2)
		return ('c');
	if (mod == 4)
		return ('d');
	if (mod == 14)
		return ('s');
	if (mod == 12)
		return ('l');
	if (mod == 10)
		return ('-');
	if (mod == 1)
		return ('p');
	return ('-');
}

int		ft_permissions(char *str, int place, int mod)
{
	int reste;

	while ((place -= 3) > 0)
	{
		if ((reste = mod % 10) == 0)
			ft_strncpy(&(str[place]), "---", 3);
		if (reste == 1)
			ft_strncpy(&(str[place]), "--x", 3);
		if (reste == 2)
			ft_strncpy(&(str[place]), "-w-", 3);
		if (reste == 3)
			ft_strncpy(&(str[place]), "-wx", 3);
		if (reste == 4)
			ft_strncpy(&(str[place]), "r--", 3);
		if (reste == 5)
			ft_strncpy(&(str[place]), "r-x", 3);
		if (reste == 6)
			ft_strncpy(&(str[place]), "rw-", 3);
		if (reste == 7)
			ft_strncpy(&(str[place]), "rwx", 3);
		mod = (mod - reste) / 10;
	}
	return (mod);
}

void	ft_mod_convert(int mod)
{
	char	str[11];
	int		place;

	str[10] = '\0';
	place = 10;
	mod = ft_permissions(&(str[0]), place, mod);
	str[0] = ft_file_type(mod);
	ft_putstr(str);
}

void	ft_time_display(time_t file_time)
{
	char	*time_str;
	char	*tofree;
	time_t	t;

	time_str = ctime(&file_time);
	tofree = ft_strsub(time_str, 4, 7);
	ft_putstr(tofree);
	free(tofree);
	t = time(0);
	if (file_time - t < 0 && file_time - t > - (365.25 * 24 * 60 * 30))
	{
		tofree = ft_strsub(time_str, 11, 5);
		ft_putstr(tofree);
		free(tofree);
	}
	else
	{
		tofree = ft_strsub(time_str, 19, 5);
		ft_putstr(tofree);
		free(tofree);
	}
}

int	ft_inspect_file(char *filepath, char *filename)
{
	struct	stat *file;
	struct	group *grp;
	struct	passwd *passwd;

	file = 0;
	file = (struct stat *)malloc(sizeof(struct stat));
	//prend les stat
	stat(filepath, file);
	// prends les infos de groupe (dont le nom)
	grp = getgrgid(file->st_gid);
	// prend les infos d'utilisateur (dans passwd) (dont le nom d'user)
	passwd = getpwuid(file->st_uid);
	// filemod
	ft_mod_convert(ft_10_to_8(file->st_mode));
	ft_putstr("  ");
	// number of links
	ft_putnbr(file->st_nlink);
	//ft_putnbr(file->st_nlink);
	ft_putstr(" ");
	// Owner name
	ft_putstr(passwd->pw_name);
	ft_putstr("  ");
	// Group name
	ft_putstr(grp->gr_name);
	ft_putstr("  ");
	// number of bytes
	ft_putnbr(file->st_size);
	ft_putstr(" ");
	// date of modif
	ft_time_display(file->st_mtimespec.tv_sec);
	ft_putstr(" ");
	// file name
	ft_putstr(filename);
	free(file);
	file = NULL;
	return (0);
}
