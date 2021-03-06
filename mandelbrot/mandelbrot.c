#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct {double re, im;} complexd;
typedef struct {unsigned int x, y;} coord;

double lerpd(double a, double b, double t);
complexd img_coords_to_complex(coord point, coord img_size, complexd top_left, complexd bottom_right);
unsigned char mandelbrot_iter(complexd c, unsigned int max_iter);

typedef struct
{
    FILE *file;
    coord size;
    unsigned int pos;
} pgm_write_info;

pgm_write_info pgm_write_hdr(FILE *f, coord img_size);
int pgm_write_pixel(pgm_write_info *i, unsigned char pixel);


int main()
{
    
    //For what c values is   z_0 = 0; z_(n+1) = z_n^2 + c   convergent?
    //simple escape condition: if |z| > 2 (|z|^2 > 4)
    coord img_size = {1920, 1080};

    complexd center = {0.0, 0.0};
    double hwidth = 2.0, hheight = hwidth * img_size.y / img_size.x;
    complexd top_left = {center.re - hwidth, center.im + hheight};
    complexd bottom_right = {center.re + hwidth, center.im - hheight};
    
    unsigned int max_iter = 50;

    char filename[32];
    time_t now = time(NULL);
    snprintf(filename, 32, "mandelbrot-%ld.pgm", now);
    FILE *f = fopen(filename, "wb");
    pgm_write_info pgm_inf = pgm_write_hdr(f, img_size);


    for(coord pos = {0, 0}; pos.y < img_size.y; pos.y++)
        for(pos.x = 0; pos.x < img_size.x; pos.x++)
        {
            unsigned char i = mandelbrot_iter(
                img_coords_to_complex(pos, img_size, top_left, bottom_right),
                max_iter);
            
            pgm_write_pixel(&pgm_inf, i);
        }

    fclose(f);

    return 0;
}


double lerpd(double a, double b, double t)
{
    return a * (1 - t) + b * t;
}

complexd img_coords_to_complex(coord point, coord img_size, complexd top_left, complexd bottom_right)
{
    complexd result;
    result.re = lerpd(top_left.re, bottom_right.re, (double)point.x / img_size.x);
    result.im = lerpd(top_left.im, bottom_right.im, (double)point.y / img_size.y);

    return result;
}

//returns 0 if c is in the set, otherwise the return value can be used for color
unsigned char mandelbrot_iter(complexd c, unsigned int max_iter)
{
    complexd z = c;
    unsigned char result = 0;

    for(unsigned int i = 1; i <= max_iter; i++)
    {
        double re2 = z.re * z.re;
        double im2 = z.im * z.im;
        if(re2 + im2 > 4)
        {
            result = 1 + i * 254 / max_iter;
            break;
        }

        //(a+bi)^2 + c + di = a*a-b*b+c + (2*a*b+d)*i 
        z.im = 2 * z.re * z.im + c.im;
        z.re = re2 - im2 + c.re;
    }

    return result;
}


pgm_write_info pgm_write_hdr(FILE *f, coord img_size)
{
    pgm_write_info info = {f, img_size, 0};

    if(!fprintf(f, "P5 %u %u 255\n", img_size.x, img_size.y))
        info.file = NULL;

    return info;
}

int pgm_write_pixel(pgm_write_info *i, unsigned char pixel)
{
    if(i->pos >= i->size.x * i->size.y) return -1;
    i->pos++;

    return fwrite(&pixel, sizeof(unsigned char), 1, i->file);
}
