/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 22:57:13 by jjolivot          #+#    #+#             */
/*   Updated: 2018/09/01 20:11:38 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_flags(int argc, char **argv, char **flags)
{
	int i;

	i = 0;
	if (argc > 1)
		if (argv[1][0] == '-')
		{
			while (argv[1][++i])
			{
				if (argv[1][i] == 'l')
					(*flags)[1] = 'l';
				if (argv[1][i] == 'r')
					(*flags)[2] = 'r';
				if (argv[1][i] == 'R')
					(*flags)[3] = 'R';
				if (argv[1][i] == 'a')
					(*flags)[0] = 'a';
				if (argv[1][i] == 't')
					(*flags)[4] = 't';
				if (argv[1][i] != 'l' && argv[1][i] != 't' && argv[1][i] != 'a'
						&& argv[1][i] != 'R' && argv[1][i] != 'r')
				{
					ft_putstr("ft_ls: illegal option -- ");
					ft_putchar(argv[1][i]);
					ft_putstr("\n");
					return (-1);
				}
			}
		}
	return (0);
}

int	ft_empty_arg(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
		if (!ft_strlen(argv[i]))
		{
			ft_putstr("ls: fts_open: No such file or directory\n");
			return (1);
		}
	return (0);
}

int	main(int argc, char **argv)
{
	char *flags;
	int i;

	if (ft_empty_arg(argc, argv))
		return (0);
	if (!(flags = (char *)malloc(sizeof(char) * 6)))
			return (-1);
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 0;
	flags[4] = 0;
	i = 0;
	if (ft_flags(argc, argv, &flags) == -1)
		return (-1);
//	if (argc == 1)
//		ft_ls(".", flags);
	if (argc == 2 && argv[1][0] == '-')
		ft_ls(".", flags);
	else if (argc == 2 && argv[1][0] != '-')
		ft_ls(argv[1], flags);
	else if (argc == 3 && argv[1][0] == '-')
		ft_ls(argv[2], flags);
	else while (argv[++i])
	{
		if (i == 1 && argv[1][0] == '-')
			i++;
		if (ft_check_permission(argv[i]) == 2)
		{
			ft_putstr(argv[i]);
			ft_putstr(":\n");
			ft_ls(argv[i], flags);
		}
	}
/**/
//	ft_ls("tests", flags);
	free(flags);
	return (0);
}
