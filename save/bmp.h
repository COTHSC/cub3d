/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 09:24:22 by jescully          #+#    #+#             */
/*   Updated: 2021/03/09 09:36:30 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BMP_H
#define _BMP_H

typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

Image* Charger(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);

#endif
 
