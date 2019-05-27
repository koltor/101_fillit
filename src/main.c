/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 13:18:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 15:41:48 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	ft_put_tab(char **tab, int fd)
{
	int i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		ft_putendl_fd(tab[i], fd);
}

t_flist	*ft_read(char *av, size_t *line)
{
	int		f;
	t_flist	*list;

	f = open(av, O_RDONLY);
	if (!(list = malloc(sizeof(t_flist))))
		return (NULL);
	list->prev = NULL;
	list->next = NULL;
	list->str = NULL;
	while (get_next_line(f, &list->str) > 0)
	{
		(*line)++;
		if (!(list->next = (t_flist*)malloc(sizeof(t_flist))))
			return (NULL);
		list->next->prev = list;
		list = list->next;
	}
	list->next = NULL;
	while (list->prev)
		list = list->prev;
	return (list);
}

char	**ft_tab_malloc(size_t size)
{
	size_t	i;
	char	**tab;

	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!(tab[i] = ft_strnew(size)))
			return (NULL);
		i++;
	}
	tab[i] = NULL;
	return (replace0(tab, size));
}

char	**replace0(char **tab, int size)
{
	int	i;
	int j;

	i = -1;
	if (!tab)
		return (NULL);
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (tab[i][j] == '\0')
				tab[i][j] = '.';
		}
	}
	return (tab);
}
/*
int		main(int ac, char **av)
{
	t_flist		*list;
	t_idxlist	*lst_index;
	char		**tab;
	size_t		line;
	size_t		size;

	line = 1;
	if (ac != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(av[0]);
		ft_putendl(" file_name");
		return (1);
	}
	list = ft_read(av[1], &line);
	if (line == 1 || line > 130 || validate_file(list))
		return (error(list));
	lst_index = ft_get_index(list);
	ft_flstdel(&list, &ft_strdel);
	size = map_size((line / 5) * 4);
	tab = fillit(lst_index, &size, 'A', ft_tab_malloc(size));
	ft_idxlstdel(&lst_index);
	ft_put_tab(tab, 1);
	free_tab(&tab, size);
	return (0);
}
*/
/*
** Instructions du main déplacées vers
** la fonction `parse_opt`
** (dans le fichier option.c)
*/


 int		main(int ac, char **av)
{
	if (ac < 2 || ac > 3)
	{
		ft_putstr("usage: ");
		ft_putstr(av[0]);
		ft_putendl(" [-u | --unicode] [-p | --palette] file_name");
		return (1);
	}
	parse_opt(ac, av);
	return (0);
}

