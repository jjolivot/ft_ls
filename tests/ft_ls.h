/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 21:55:29 by jjolivot          #+#    #+#             */
/*   Updated: 2018/07/23 16:10:51 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct	s_pn
{
	struct s_pn	*prev;
	char	*pathname;
	char	*filename;
	char	*toprint;
	char	filetype;
	struct s_pn	*next;
}				t_pn;

int ft_inspect_file(char *file, char *filename);

#endif
