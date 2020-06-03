#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct {double re, im;} complexd;
typedef struct {unsigned int x, y;} coord;

double lerpd(double a, double b, double t);
complexd img_coords_to_complex(coord point, coord img_size, complexd top_left, complexd bottom_right);
unsigned char julia_iter(complexd z, complexd c, unsigned int max_iter);

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
    coord img_size = {1920, 1080};

    complexd center = {0.0, 0.0};
    double hwidth = 2.5, hheight = hwidth * img_size.y / img_size.x;
    complexd top_left = {center.re - hwidth, center.im + hheight};
    complexd bottom_right = {center.re + hwidth, center.im - hheight};

    complexd julia_c = {0.5, 0.0};
    unsigned int max_iter = 250;

    char filename[32];
    time_t now = time(NULL);
    snprintf(filename, 32, "julia-%ld.pgm", now);
    FILE *f = fopen(filename, "wb");
    pgm_write_info pgm_inf = pgm_write_hdr(f, img_size);


    for(coord pos = {0, 0}; pos.y < img_size.y; pos.y++)
        for(pos.x = 0; pos.x < img_size.x; pos.x++)
        {
            char i = julia_iter(
                img_coords_to_complex(pos, img_size, top_left, bottom_right),
                julia_c, max_iter);
            
            pgm_write_pixel(&pgm_inf, i);
        }

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

//returns 0 if z is in the (filled) set, otherwise the return value can be used for color
unsigned char julia_iter(complexd z, complexd c, unsigned int max_iter)
{
    for(unsigned int i = 1; i <= max_iter; i++)
    {
        if(z.re < -10 || z.re > 10 || z.im < -10 || z.im > 10)
            break;

        complexd z_next = {z.re * (z.re*z.re - 3*z.im*z.im) + c.re, z.im * (3*z.re*z.re - z.im*z.im) + c.im};
        z = z_next;
    }

    if((z.re > -10 && z.re < 10) || (z.im > -10 && z.im < 10))
        return 0;

    return 255;
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
