/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:29 by stafpec           #+#    #+#             */
/*   Updated: 2025/01/10 17:54:53 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_and_clean_content(t_list **container)
/* clean list after the extract */
{
	t_list	*tmp;
	char	*newline;
	char	*new_content;

	while (*container)
	{
		newline = ft_strdup_or_strchr((*container)->content, '\n', 0);
		if (newline)
		{
			new_content = ft_strdup_or_strchr(newline + 1, 0, 1);
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

char	*ft_strdup_or_strchr(const char *s, int c, int flag)
{
	int		i;
	char	*dest;

	i = -1;
	if (flag == 1)
	{
		while (s[++i])
			;
		dest = malloc(sizeof(char) * (i + 1));
		if (dest == NULL)
			return (NULL);
		i = -1;
		while (s[++i])
			dest[i] = s[i];
		dest[i] = '\0';
		return (dest);
	}
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
/* allocates (with malloc(3)) and returns a new element */
{
	t_list	*current;

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
/* add element ’new’ at the end of list */
{
	t_list	*my_new_list;

	my_new_list = malloc(sizeof(t_list));
	if (my_new_list == NULL)
		return (NULL);
	my_new_list->content = content;
	my_new_list->next = NULL;
	return (my_new_list);
}

void	ft_lstclear_all(t_list **list)
{
	t_list	*current;
	t_list	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*list = NULL;
}
