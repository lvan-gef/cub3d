#include "../../include/cub3d_parser.h"


static const char	*g_labels[SIZE] = {"NO", "SO", "WE", "EA", "F", "C"};

static char	*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	a;
	size_t	b;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
	{
		free ((char *)s1);
		free ((char *)s2);
		return (NULL);
	}
	a = ft_strlen(s1);
	b = 0;
	ft_memcpy(str, s1, a);
	while (s2[b])
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	free((char *)s1);
	return (str);
}

// Place the identifiers in the right order for parsing.
// Pre check for double elements.
static int	is_identifier(char *trimmed_line, char **elements)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			// if (elements[i] != '\0')  // think we have to replace it with a NULL check now it is a pointer to a null-char
			if (elements[i] != NULL)  // think we have to replace it with a NULL check now it is a pointer to a null-char
				print_error("invalid object input");  // leaks elements, and line (from gnl plus if the file is not fully parsed also the buffer from gnl) and open file fd
			if (i < 4)
				elements[i] = ft_substr(trimmed_line, 2, (ft_strlen(trimmed_line) - 2));  // why minus 2 and add NULL check
			else
				elements[i] = ft_substr(trimmed_line, 1, (ft_strlen(trimmed_line) - 1));  // why minus 1 and add NULL check
			temp = ft_strtrim(elements[i], WHITESPACE);  // add NULL check
			free(elements[i]);
			elements[i] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

// Get input line by line.
// Check if the line contains identifier or map input.
// Handle as such:
// Use the trimmed line for elements, untrimmed line for the map.
// Pre check for the left trimmed lines in the map (has to be 1).
static void	get_elements(int fd, char **elements)
{
	char		*line;
	char		*trimmed_line;
	int			flag;

	flag = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, WHITESPACE);  // NULL check toevoegen
		if (trimmed_line[0] && flag == 1)
			flag = is_identifier(trimmed_line, elements);
		if (flag == 0)
		{
			if (trimmed_line[0] == '1')
				elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line); // can return NULL but we dont do something with it yet, if return NULL we have dubble free on line
			else
				print_error("Invalid input: Invalid map");  // leaks elements, and line (from gnl plus if the file is not fully parsed also the buffer from gnl) and trimmed_line, and open file fd
		}
		free(trimmed_line);
		free(line);
	}
}

// allocate space for the elements & fill the char pointer with tokenized input.
char	**tokenize_input(char *argv)
{
	int			fd;
	char		**elements;

	elements = ft_calloc(SIZE + 1, sizeof(char *));  // NULL check toevoegen
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("File opening failed.");  // free elements toevoegen
	get_elements(fd, elements);
	close(fd);
	return (elements);
}
