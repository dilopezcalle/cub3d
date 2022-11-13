/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/13 15:28:08 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "structs.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_content	*content;

	if (argc != 2)
		return (printf("Error: Argumentos invalidos\n"));
	content = parser(argv[1]);
	if (!content)
		return (1);
	return (0);
}
