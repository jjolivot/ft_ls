/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 19:42:41 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/26 02:14:12 by jjolivot         ###   ########.fr       */
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


struct s_pn *ft_sort(struct s_pn *maillon, char *flags)
{
	struct s_pn *tmp;
	struct s_pn *first;


	first = maillon;
		while (maillon->next)
		{
			if (maillon->next && maillon->modif_time < maillon->next->modif_time && flags[4] == 't')
			{
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
			maillon = maillon->next;
		}
	maillon = first;
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
