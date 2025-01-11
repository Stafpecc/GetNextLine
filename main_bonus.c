/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:31:25 by tarini            #+#    #+#             */
/*   Updated: 2025/01/11 17:33:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int fd1 = open("test", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);

	char *line;

	line = get_next_line(fd1);
	printf("\nFile1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("\nFile2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("\nFile1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("\nFile2: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	return 0;
}
