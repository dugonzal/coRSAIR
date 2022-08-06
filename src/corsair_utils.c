/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:06:25 by vscode            #+#    #+#             */
/*   Updated: 2022/08/06 07:50:25 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corsair.h"

size_t ft_strlen(const unsigned char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
