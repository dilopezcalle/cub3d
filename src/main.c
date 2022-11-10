/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/10 12:00:59 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("Error\n"));
	if (parser(argv[1]))
		return (printf("Error\n"));
	return (0);
}