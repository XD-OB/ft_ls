/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:47:50 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 12:22:47 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_arg(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	if (*(file->nbr_dir) > 1 && !S_ISREG(file->stats->st_mode))
	{
		if (*(file->nbr_reg))
			ft_putchar('\n');
		else
			(*(file->nbr_reg))++;
		ft_printf("%s:\n", file->name);
	}
	if (*(file->nbr_dir) == 1 && *(file->nbr_reg) > 0
			&& !S_ISREG(file->stats->st_mode))
		ft_printf("\n%s:\n", file->name);
	ft_ls(item);
}

int				main(int ac, char **av)
{
	t_ls	ls;

	parse(ac, av, &ls);
	bt_apply_infix(ls.invtree, print_enoent);
	bt_apply_infix(ls.root, ls_arg);
	bt_free(&ls.invtree, &freef);
	bt_free(&ls.root, &freef);
	return (0);
}
