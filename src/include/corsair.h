/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:02 by ciclo             #+#    #+#             */
/*   Updated: 2022/08/05 12:49:37 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CORS_AIR_H
# define CORS_AIR_H


#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <fcntl.h>

#include <unistd.h>

size_t	ft_strlen(const unsigned char *str);
void	rsa_gen_keys(void);

#endif
