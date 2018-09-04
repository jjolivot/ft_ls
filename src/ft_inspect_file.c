/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:09:05 by jjolivot          #+#    #+#             */
/*   Updated: 2018/08/29 16:14:48 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

char	*ft_mod_convert(int mod)
{
	char	*str;
	int		place;

	if (!(str = (char *)malloc(sizeof(char) * 10 + 1)))
		exit(0);;
	str[10] = '\0';
	place = 10;
	mod = ft_permissions(&(str[0]), place, mod);
	str[0] = ft_file_type(mod);
	return (str);
}

char	*ft_time_display(time_t file_time)
{
	char	*time_str;
	char	*tofree;
	time_t	t;

	time_str = ctime(&file_time);
	tofree = ft_strsub(time_str, 4, 7);
	t = time(0);
	if (file_time - t < 0 && file_time - t > - (365.25 * 24 * 60 * 30))
	{
		tofree = ft_f_strjoin(tofree, (time_str = ft_strsub(time_str, 11, 5)));
		free(time_str);
		return (tofree);
	}
	else
	{
		tofree = ft_f_strjoin(tofree, (time_str = ft_strsub(time_str, 19, 5)));
		free(time_str);
		return (tofree);
	}
}

char	*ft_inspect_file(char *filepath, char *filename, time_t *modif_time)
{
	struct	stat *file;
	struct	group *grp;
	struct	passwd *passwd;
	char	*ext_print;
	char	*tmp; // Au pire, il reste un argument

	file = 0;
	if (!(file = (struct stat *)malloc(sizeof(struct stat))))
		exit(0);
	//prend les stat
	lstat(filepath, file);
	// prends les infos de groupe (dont le nom)
	grp = getgrgid(file->st_gid);
	// prend les infos d'utilisateur (dans passwd) (dont le nom d'user)
	passwd = getpwuid(file->st_uid);
	// filemod
	ext_print = ft_mod_convert(ft_10_to_8(file->st_mode));
	ext_print = ft_f_strjoin(ext_print, "\t");
	// number of links
	ext_print = ft_f_strjoin(ext_print, (tmp = ft_itoa(file->st_nlink)));
	free(tmp);
	//ft_putnbr(file->st_nlink);
	ext_print = ft_f_strjoin(ext_print, "\t");
	// Owner name
	ext_print = ft_f_strjoin(ext_print, passwd->pw_name);
	ext_print = ft_f_strjoin(ext_print, "\t");
	// Group name
	ext_print = ft_f_strjoin(ext_print, grp->gr_name);
	ext_print = ft_f_strjoin(ext_print, "\t");
	// number of bytes
	ext_print = ft_f_strjoin(ext_print, (tmp = ft_itoa(file->st_size)));
	free(tmp);
	ext_print = ft_f_strjoin(ext_print, "\t");
	// date of modif
	ext_print = ft_f_strjoin(ext_print, (tmp = ft_time_display(file->st_mtimespec.tv_sec)));
	free(tmp);
	if (modif_time)
		*modif_time = file->st_mtimespec.tv_sec;
	ext_print = ft_f_strjoin(ext_print, "\t");
	// file name
	ext_print = ft_f_strjoin(ext_print, filename);
	if (ext_print[0] == 'l')
	{
		ext_print = ft_f_strjoin(ext_print, " -> ");
		if (!(tmp = (char *)malloc(sizeof(char) * 4096 + 1)))
				exit(0);
		tmp[readlink(filepath, tmp, 4096)] = '\0';
		ext_print = ft_f_strjoin(ext_print, tmp);
		free(tmp);
	}
	free(file);
	file = NULL;
	return (ext_print);
}
