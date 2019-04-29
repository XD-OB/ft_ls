/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:41:42 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 14:29:56 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_orglink(t_file *file)
{
	char	*buff;

	if (is_large(file->opts) &&
		S_ISLNK(file->stats->st_mode))
	{
		write(1, " -> ", 4);
		buff = ft_strnew(BUFF_SIZE);
		readlink(file->path, buff, BUFF_SIZE);
		ft_putstr(buff);
		free(buff);
	}
}

void		print_name(t_file *file)
{
	if (is_exec(file))
		ft_printf("%{PURPLE}%s%{eoc}", file->name);
	else if (S_ISREG(file->stats->st_mode))
		ft_printf("%s", file->name);
	else if (S_ISDIR(file->stats->st_mode))
		ft_printf("%{CYAN}%s%{eoc}", file->name);
	else if (S_ISLNK(file->stats->st_mode))
		ft_printf("%{red}%s%{eoc}", file->name);
	else if (S_ISCHR(file->stats->st_mode))
		ft_printf("%{BLUE}%s%{eoc}", file->name);
	else if (S_ISBLK(file->stats->st_mode))
		ft_printf("%{blue}%s%{eoc}", file->name);
	else if (S_ISFIFO(file->stats->st_mode))
		ft_printf("%{yellow}%s%{eoc}", file->name);
	else if (S_ISSOCK(file->stats->st_mode))
		ft_printf("%{green}%s%{eoc}", file->name);
}

void		print_name_p(t_file *file)
{
	if (is_exec(file))
		ft_printf("%{PURPLE}%s/%{eoc}", file->name);
	else if (S_ISREG(file->stats->st_mode))
		ft_printf("%s/", file->name);
	else if (S_ISDIR(file->stats->st_mode))
		ft_printf("%{CYAN}%s/%{eoc}", file->name);
	else if (S_ISLNK(file->stats->st_mode))
		ft_printf("%{red}%s/%{eoc}", file->name);
	else if (S_ISCHR(file->stats->st_mode))
		ft_printf("%{BLUE}%s/%{eoc}", file->name);
	else if (S_ISBLK(file->stats->st_mode))
		ft_printf("%{blue}%s/%{eoc}", file->name);
	else if (S_ISFIFO(file->stats->st_mode))
		ft_printf("%{yellow}%s/%{eoc}", file->name);
	else if (S_ISSOCK(file->stats->st_mode))
		ft_printf("%{green}%s/%{eoc}", file->name);
}

int			print_column(t_file *file, int is_p)
{
	if (file->opts->c)
	{
		ft_printf("%-20s", file->name);
		if (is_p)
			ft_putchar('/');
		if (--file->c_mw->count % 3 == 0)
			ft_putchar('\n');
		return (1);
	}
	return (0);
}

void		print_item(void *item)
{
	t_file			*file;
	char			*s;
	int				is_p;

	file = (t_file*)item;
	is_p = (file->opts->p && S_ISDIR(file->stats->st_mode)) ? 1 : 0;
	s = (file->opts->m) ? ", " : "\n";
	if (file->opts->i)
		ft_printf("%ld ", (long)file->stats->st_ino);
	if (is_large(file->opts))
		print_lgformat(file);
	if (print_column(file, is_p))
		return ;
	if (file->opts->cap_g)
		(is_p) ? print_name_p(file) : print_name(file);
	else
	{
		ft_putstr(file->name);
		if (is_p)
			ft_putchar('/');
	}
	print_orglink(file);
	ft_putstr((--file->c_mw->count) ? s : "\n");
}
