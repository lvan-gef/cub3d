/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.42.fr>              +#+                   */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by lvan-gef       #+#    #+#                */
/*   Updated: 2024/11/22 18:40:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_check_edge_case(int fd)
{
	char	*line;

	if (errno != 0)
	{
		while (1)
		{
			line = get_next_line(fd);
			if (line == NULL)
				break ;
			free(line);
		}
	}
}

static	bool	_is_identifier(const char *line, char **elements)
{
	static const char	*labels[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int					i;

	i = 0;
	errno = 0;
	while (i < SIZE)
	{
		while (*line == ' ')
			line++;
		if (!ft_strncmp(line, labels[i], ft_strlen(labels[i])))
		{
			free(elements[i]);
			elements[i] = _parse_ident(elements, i, line);
			return (false);
		}
		if (line[0] == '\n')
			return (false);
		i++;
	}
	return (true);
}

static void	_get_elements(int fd, char **elements)
{
	char	*line;
	bool	flag;
	bool	is_map;

	is_map = false;
	while (1)
	{
		flag = true;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (flag == true)
		{
			flag = _is_identifier(line, elements);
			if (flag == true)
				is_map = true;
		}
		if (errno != 0)
			break ;
		if (_check_token(line, elements, flag, is_map) != true)
			break ;
		free(line);
	}
	free(line);
	_check_edge_case(fd);
}

char	**tokenize_input(char *argv)
{
	int			fd;
	char		**elements;

	elements = ft_calloc(SIZE + 1, sizeof(*elements));
	if (elements == NULL)
	{
		ft_putendl_fd("failed to calloc elements", 2);
		return (NULL);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Failed to open the map", 2);
		return (elements);
	}
	_get_elements(fd, elements);
	close(fd);
	return (elements);
}
