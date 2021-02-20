/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:56:56 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/29 14:29:10 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		set_m(t_ls *ls)
{
	ls->opts.m = 1;
	ls->opts.l = 0;
	ls->opts.o = 0;
	ls->opts.g = 0;
	ls->opts.n = 0;
	ls->opts.c = 0;
}

static void		set_no_m(t_ls *ls, char c)
{
	(c == 'l') ? ls->opts.l = 1 : 0;
	(c == 'o') ? ls->opts.o = 1 : 0;
	(c == 'g') ? ls->opts.g = 1 : 0;
	(c == 'n') ? ls->opts.n = 1 : 0;
	ls->opts.m = 0;
	ls->opts.c = 0;
}

static void		set_t(t_ls *ls)
{
	ls->opts.t = 1;
	ls->opts.u = 0;
}

static void		set_c(t_ls *ls)
{
	ls->opts.c = 1;
	ls->opts.l = 0;
	ls->opts.o = 0;
	ls->opts.g = 0;
	ls->opts.n = 0;
	ls->opts.m = 0;
}

void			add_opts(t_ls *ls, char *s)
{
	while (*(++s))
	{
		if (!ft_strchr("1lartuiogmpncRSAG", *s))
		{
			write(2, "ft_ls: illegal option -- ", 22);
			ft_putchar_fd(*s, 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("usage: ft_ls [-1lartuiogmpncRSAG] [file ...]\n", 2);
			exit(1);
		}
		(*s == 't') ? set_t(ls) : 0;
		(*s == 'm') ? set_m(ls) : 0;
		(*s == '1') ? ls->opts.l = 0 : 0;
		(*s == 'a') ? ls->opts.a = 1 : 0;
		(*s == 'r') ? ls->opts.r = 1 : 0;
		(*s == 'i') ? ls->opts.i = 1 : 0;
		(*s == 'p') ? ls->opts.p = 1 : 0;
		(*s == 'u') ? ls->opts.u = 1 : 0;
		(*s == 'c') ? set_c(ls) : 0;
		(*s == 'R') ? ls->opts.cap_r = 1 : 0;
		(*s == 'S') ? ls->opts.cap_s = 1 : 0;
		(*s == 'A') ? ls->opts.cap_a = 1 : 0;
		(*s == 'G') ? ls->opts.cap_g = 1 : 0;
		(ft_strchr("lgon", *s)) ? set_no_m(ls, *s) : 0;
	}
}
