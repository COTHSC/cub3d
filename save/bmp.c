#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "bmp.h"
#include "../cub3d.h"
#include <fcntl.h>

Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

Image* CopieImage(Image* I)
{
	Image* res;
	if (!I)
		return NULL;
	res = NouvelleImage(I->w,I->h);
	memcpy(res->dat,I->dat,I->w*I->h*sizeof(Pixel));
	return res;
}

void DelImage(Image* I)
{
	if (I)
	{
		free(I->dat);
		free(I);
	}
}

void SetPixel(Image* I,int i,int j,Pixel p)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	I->dat[I->w*j+i] = p;
}

Pixel GetPixel(Image* I,int i,int j)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	return I->dat[I->w*j+i];
}

typedef int int32;
typedef short int16;

void    ft_header(t_vars *vars, int fd)
{
    int tmp;
	int tmp2;

    write(fd, "BM", 2);
    tmp = 14 + 40 + 4 * vars->res->h * vars->res->w;
    write(fd, &tmp, 4);
    tmp = 0;
    write(fd, &tmp, 2);
    write(fd, &tmp, 2);
    tmp = 54;
    write(fd, &tmp, 4);
    tmp = 40;
    write(fd, &tmp, 4);
	tmp2 = vars->res->w;
    write(fd, &tmp2, 4);
    write(fd, &tmp2, 4);
    tmp = 1;
    write(fd, &tmp, 2);
	tmp2 = vars->img->bpp;
    write(fd, &tmp2, 2);
    tmp = 0;
    write(fd, &tmp, 4);
    write(fd, &tmp, 4);
    write(fd, &tmp, 4);
    write(fd, &tmp, 4);
    write(fd, &tmp, 4);
    write(fd, &tmp, 4);
}

int save_img(t_vars *vars,const char* fichier)
{
	int i,j,tailledata,pitch;
	unsigned char bgrpix[3];
	int fd;
    fd = open("./save/screenshot.bmp", O_CREAT|O_RDWR, S_IRWXU|S_IRWXG);	
	ft_header(vars, fd);
	for(j=vars->res->h;j > 0;j--)
	{
		for(i=0;i<vars->res->w;i++)
		{
			write(fd, &vars->img->data[j * vars->res->w + i], 4);
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
//		write(fd, &bgrpix, pitch);
	}
	close(fd);
	return 0;
}
