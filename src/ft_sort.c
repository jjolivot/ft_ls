/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 19:42:41 by jjolivot          #+#    #+#             */
/*   Updated: 2018/08/29 20:05:50 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_count(struct s_pn *maillon)
{
	int i;

	i = 0;
	while (maillon->next)
	{
		maillon = maillon->next;
		i++;
	}
	return (i);
}

struct s_pn *ft_alpha_sort(struct s_pn *maillon, struct s_pn *first)
{
	struct s_pn *tmp;

	if (maillon->prev)
		maillon->prev->next = maillon->next;
	if(maillon->next->next)
		maillon->next->next->prev = maillon;
	maillon->next->prev = maillon->prev;
	maillon->prev = maillon->next;
	tmp = maillon->next->next;
	maillon->next->next = maillon;
	maillon->next = tmp;
	while (first->prev)
		first = first->prev;
	maillon = first;
		return (maillon);
}

struct s_pn *ft_flags_sort(struct s_pn *maillon, struct s_pn *midmaillon, char *flags)
{
	struct s_pn *tmp;

	if (flags[4] == 't')
	{
		if (maillon->modif_time < midmaillon->modif_time)
		{
			tmp = maillon;
			maillon = midmaillon;
			while (maillon->next)
				maillon = maillon->next;
			maillon->next = tmp;
			tmp->prev = maillon;
		}
		else
		{
			while (maillon->next)
				maillon = maillon->next;
			maillon->next = midmaillon;
			midmaillon->prev = maillon;
		}
	}
	else
//		maillon = ft_alpha_sort(maillon, midmaillon);
	while (maillon->prev)
		maillon = maillon->prev;
	return (maillon);
}


/*struct s_pn *ft_sort(struct s_pn *maillon, char *flags)
{
	int	i;
	int	count;
	struct s_pn *mid;

	i = -1;
	mid = maillon;
	count = ft_count(maillon);
	while (i++ < count / 2 + 1)
		mid = mid->next;
//	if (mid->prev)
//		mid->prev->next = NULL;
//liste bien coupe en deux
	
	if (ft_count(mid) > 0)
		mid = ft_sort(mid, flags);
	printf("ca passe %i \n", count);
	if (ft_count(maillon) > 0)
		maillon = ft_sort(maillon, flags);
	maillon = ft_flags_sort(maillon, mid, flags);
	return (maillon);
}*/

struct s_pn	*ft_invert_list(struct s_pn *maillon)
{
	struct s_pn *tmp;
	int i;

	i = 0;
	while (maillon->prev || i++ == 0)
	{
		tmp = maillon->next;
		maillon->next = maillon->prev;
		maillon->prev = tmp;
		if (tmp)
			maillon = tmp;
	}
	return (maillon);
}

struct s_pn *ft_sort(struct s_pn *maillon, char *flags)
{
	struct s_pn *tmp;
	struct s_pn *first;


	first = maillon;
		while (maillon->next)
		{
//			printf("%s\n", maillon->filename);
			if ((maillon->modif_time <
			maillon->next->modif_time && flags[4] == 't'))/* ||
			((!ft_is_alpha_sort(maillon->filename, maillon->next->filename) && flags[4] != 't')))*/
			{
				if (maillon->prev)
					maillon->prev->next = maillon->next;
				if(maillon->next->next)
					maillon->next->next->prev = maillon;
				maillon->next->prev = maillon->prev;
				maillon->prev = maillon->next;
				tmp = maillon->next->next;
				maillon->next->next = maillon;
				maillon->next = tmp;
				while (first->prev)
					first = first->prev;
				maillon = first;
			}
			if (flags[4] != 't' && ft_strcmp(maillon->filename, maillon->next->filename) > 0)
				maillon = ft_alpha_sort(maillon, first);
//			printf("%s\n", maillon->filename);
			maillon = maillon->next;
		}
	maillon = first;
	if (flags[2] == 'r')
		maillon = ft_invert_list(maillon);
	return (maillon);
}

/*
struct s_pn *ft_sort(struct s_pn *maillon, char *flags)
{
	int		count;
	int		i;
	struct	s_pn *midmaillon;

	i = 0;
	midmaillon = maillon;
	if ((count = ft_count(maillon)) == 0)
		return (maillon);
//	printf("count = %i\n", count);
	count = count / 2 + 1;
	while (i++ < count)
		midmaillon = midmaillon->next;
	midmaillon->prev->next = NULL;
	midmaillon->prev = NULL;
	if (ft_count(midmaillon) > 0)
		midmaillon = ft_sort(midmaillon, flags);
	if (ft_count(maillon) > 0)
		maillon = ft_sort(maillon, flags);
	maillon = ft_flags_sort(maillon, midmaillon, flags);
	return (maillon);

}*/
