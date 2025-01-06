/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:29 by stafpec           #+#    #+#             */
/*   Updated: 2025/01/06 13:33:54 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_and_clean_content(t_list **container)
{
	t_list	*tmp;
	char	*newline_pos;
	char	*new_content;

	while (*container)
	{
		newline_pos = ft_strchr((*container)->content, '\n');
		if (newline_pos)
		{
			new_content = ft_strdup(newline_pos + 1);
			free((*container)->content);
			(*container)->content = new_content;
			return ;
		}
		tmp = *container;
		*container = (*container)->next;
		free(tmp->content);
		free(tmp);
	}
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (!s)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i++])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;

	i = 0;
	while (str[i++])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(&str[i]));
	}
	if (!(unsigned char)c)
		return ((char *)(&str[i]));
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	struct s_list	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_list	*ft_lstnew(void *content)
{
	struct s_list	*my_new_list;

	my_new_list = malloc(sizeof(t_list));
	if (my_new_list == NULL)
		return (NULL);
	my_new_list->content = content;
	my_new_list->next = NULL;
	return (my_new_list);
}
