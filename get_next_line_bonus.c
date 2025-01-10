/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:23:29 by tarini            #+#    #+#             */
/*   Updated: 2025/01/10 17:55:22 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_and_store(t_list **container, int fd)
/* reads file and stores data in linked list */
{
	char		*buffer;
	int			reading;
	t_list		*new_node;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (1)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading <= 0)
			return (free(buffer), reading);
		buffer[reading] = '\0';
		new_node = ft_lstnew(ft_strdup_or_strchr(buffer, 0, 1));
		if (!new_node)
			return (ft_lstclear_all(container), free(buffer), -1);
		ft_lstadd_back(container, new_node);
		if (ft_strdup_or_strchr(buffer, '\n', 0))
			break ;
	}
	return (free(buffer), reading);
}

static size_t	compute_line_length(t_list *container)
/* calculates length of the next line */
{
	size_t	length;
	char	*content;

	length = 0;
	while (container)
	{
		content = container->content;
		while (*content && *content != '\n')
		{
			length++;
			content++;
		}
		if (*content == '\n')
		{
			length++;
			break ;
		}
		container = container->next;
	}
	return (length);
}

static void	copy_to_line(t_list *container, char *line)
/* copy to line XD */
{
	size_t	i;
	char	*content;

	i = 0;
	while (container)
	{
		content = container->content;
		while (*content && *content != '\n')
			line[i++] = *content++;
		if (*content == '\n')
		{
			line[i++] = *content;
			return ;
		}
		container = container->next;
	}
}

static char	*extract_line(t_list **container)
/* extracts the line from the list */
{
	size_t	line_len;
	char	*line;

	if (!*container)
		return (NULL);
	line_len = compute_line_length(*container);
	if (line_len == 0)
		return (NULL);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	copy_to_line(*container, line);
	line[line_len] = '\0';
	update_and_clean_content(container);
	return (line);
}

char *get_next_line(int fd)
/* returns extracted line */
{
	static t_list	*fd_data[OPEN_MAX];
	char			*line;
	int				i;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	i = -1;
	while (i < OPEN_MAX)
	{
		if (fd_data[++i])
			ft_lstclear_all(&fd_data[i]);
	}
	if (read_and_store(&fd_data[fd], fd) < 0)
		return (NULL);

	line = extract_line(&fd_data[fd]);
	update_and_clean_content(&fd_data[fd]);

	return (line);
}
