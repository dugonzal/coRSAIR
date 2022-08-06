/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:52:02 by dugonzal          #+#    #+#             */
/*   Updated: 2022/08/06 09:03:15 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corsair.h"

/*
1. Un cliente (por ejemplo, un navegador) envía su clave pública al servidor y solicita algunos datos.
2. El servidor cifra los datos utilizando la clave pública del cliente y envía los datos cifrados.
3. El cliente recibe estos datos y los descifra.
*/

int	main(void)
{
	// mensaje a encriptar
	const unsigned char msg[] = "Decifre el mensaje!";
	printf("\nMensaje a encriptar: {%s}\n", msg);
	// iniciando  keys
	rsa_gen_keys();
	printf("\nRSA keys generated successfully\n\n");
	// leer clave publica de archivo y guardarla en una estructura RSA
	RSA *rsa = NULL; // inicializar estructura RSA en NULL
	BIO *bio_public = NULL; // inicializar estructura BIO en NULL para leer clave publica de archivo
	bio_public = BIO_new_file("../keys/public.key", "r"); // abrir archivo para leer clave publica de archivo
	if(bio_public == NULL) 	// si no se pudo abrir archivo para leer clave publica de archivo
	{
		printf("\nError opening public.key file\n");
		return (1);
	}
	rsa = PEM_read_bio_RSAPublicKey(bio_public, NULL, NULL, NULL); // leer clave publica de archivo y guardarla en una estructura RSA
	if(rsa == NULL)	// si no se pudo leer clave publica de archivo
	{
		printf("\nError reading public.key file\n");
		return (1);
	}
	// encriptar mensaje
	unsigned char *enc_msg = NULL; // inicializar estructura unsigned char en NULL para almacenar mensaje encriptado
	int enc_len = 0; // inicializar  int en 0 para almacenar longitud de mensaje encriptado
	enc_len = RSA_size(rsa); // obtener longitud de mensaje encriptado la funcion RSA_size() se usa para obtener longitud de mensaje encriptado
	enc_msg = (unsigned char *)malloc(enc_len + 1); // reservar memoria para almacenar mensaje encriptado
	memset(enc_msg, 0, enc_len + 1); // inicializar memoria reservada para almacenar mensaje encriptado con valor 0
	int enc_ret = 0; // inicializar int en 0 para almacenar retorno de funcion RSA_public_encrypt()
	enc_ret = RSA_public_encrypt(ft_strlen(msg), (unsigned char *)msg, enc_msg, rsa, RSA_PKCS1_PADDING); // encriptar mensaje la funcion RSA_public_encrypt() se usa para encriptar mensaje
	if(enc_ret == -1)
	{
		printf("Error encrypting message\n");
		return (1);
	}
	// imprimir mensaje encriptado
	printf("Mensaje encriptado: ");
	int i = 0; // inicializar int en 0 para almacenar contador de iteraciones
	while(i < enc_ret) // iterar sobre mensaje encriptado
	{
		printf("%02x", enc_msg[i]); // imprimir mensaje encriptado en formato hexadecimal
		i++; // incrementar contador de iteraciones
	}
	//printf("%zu",ft_strlen (enc_msg));
	printf("\n");
	// guardar mensaje encriptado en archivo
	//FILE *fp = NULL;
	//fp = fopen("enc_msg.txt", "w");
	//fwrite(enc_msg, enc_ret, 1, fp);
	//fclose(fp);
	// leer clave privada de archivo y guardarla en una estructura RSA
	RSA *rsa_private = NULL;
	BIO *bio_private = NULL;
	bio_private = BIO_new_file("../keys/private.key", "r");
	if(bio_private == NULL)
	{
		printf("Error opening private key file\n");
		return (1);
	}
	rsa_private = PEM_read_bio_RSAPrivateKey(bio_private, NULL, NULL, NULL);
	if(rsa_private == NULL)
	{
		printf("Error reading private key\n");
		return (1);
	}
	// desencriptar mensaje
	unsigned char *dec_msg = NULL;
	int dec_len = 0;
	dec_len = RSA_size(rsa_private);
	dec_msg = (unsigned char *)malloc(dec_len + 1);
	memset(dec_msg, 0, dec_len + 1);
	int dec_ret = 0;
	dec_ret = RSA_private_decrypt(enc_ret, enc_msg, dec_msg, rsa_private, RSA_PKCS1_PADDING);
	if(dec_ret == -1)
	{
		printf("Error decrypting message\n");
		return (1);
	}
	// imprimir mensaje desencriptado
	printf("\nMensaje desencriptado: {%s}\n", dec_msg);
	// guardar mensaje desencriptado en archivo
	//fp = fopen("dec_msg.txt", "w");
	//fwrite(dec_msg, dec_ret, 1, fp);
	//fclose(fp);
	// liberar memoria
	free(enc_msg);
	free(dec_msg);
	RSA_free(rsa);
	RSA_free(rsa_private);
	BIO_free_all(bio_public);
	BIO_free_all(bio_private);
	return (0);
}
