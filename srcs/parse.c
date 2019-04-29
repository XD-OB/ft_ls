/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:27:06 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/29 11:21:34 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	parse_default(int i, int ac, t_ls *ls)
{
	t_file	*file;

	if (i == ac)
	{
		file = init_file(".", "", &ls->opts);
		file->nbr_dir = &ls->nbr_dir;
		file->nbr_reg = &ls->nbr_reg;
		ls->nbr_dir++;
		ls->nbr_reg = 0;
		fill_mw(&ls->mw, file);
		bt_insert_item(&ls->root, file, ft_cmp);
		return (1);
	}
	return (0);
}

void		parse(int ac, char **av, t_ls *ls)
{
	t_file		*file;
	int			i;

	i = 1;
	init_opts(ls);
	init_mw(&ls->mw);
	while (i < ac && av[i][0] == '-')
		add_opts(ls, av[i++]);
	if (parse_default(i, ac, ls))
		return ;
	while (i < ac)
	{
		file = init_file(av[i++], "", &ls->opts);
		file->nbr_dir = &ls->nbr_dir;
		file->nbr_reg = &ls->nbr_reg;
		if (file->error)
			bt_insert_item(&ls->invtree, file, ft_cmp_enoent);
		else
		{
			(S_ISDIR(file->stats->st_mode)) ? ls->nbr_dir++ : ls->nbr_reg++;
			fill_mw(&ls->mw, file);
			bt_insert_item(&ls->root, file, ft_cmp_arg);
		}
	}
}
