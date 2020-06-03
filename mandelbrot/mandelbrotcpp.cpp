#include <iostream>
#include <fstream>
#include <string>
#include <complex>

#include <ctime>

typedef std::pair<unsigned int, unsigned int> coord;

inline double lerp(double a, double b, double t);
std::complex<double> img_coords_to_complex(coord point, coord img_size,
                                           std::complex<double> top_left, std::complex<double> bottom_right);
unsigned char mandelbrot_iter(std::complex<double> c, unsigned int max_iter);

void pgm_write_hdr(std::ofstream& fs, coord img_size);


int main()
{
    
    //For what c values is   z_0 = 0; z_(n+1) = z_n^2 + c   convergent?
    //simple escape condition: if |z| > 2 (|z|^2 > 4)
    coord img_size = {1920, 1080};

    std::complex<double> center(0.0, 0.0);
    double hwidth = 2.0, hheight = hwidth * img_size.second / img_size.first;
    std::complex<double> top_left(center.real() - hwidth, center.imag() + hheight);
    std::complex<double> bottom_right(center.real() + hwidth, center.imag() - hheight);
    unsigned int max_iter = 50;

    std::ofstream of("mandelbrot-" + std::to_string(time(NULL)) + ".pgm", std::ios::out | std::ios::binary);
    pgm_write_hdr(of, img_size);


    for(coord pos(0, 0); pos.second < img_size.second; pos.second++)
        for(pos.first = 0; pos.first < img_size.first; pos.first++)
        {
            char i = mandelbrot_iter(
                img_coords_to_complex(pos, img_size, top_left, bottom_right),
                max_iter);
            
            of.write(&i, 1);
        }

    return 0;
}

inline double lerp(double a, double b, double t)
{
    return a * (1 - t) + b * t;
}

std::complex<double> img_coords_to_complex(coord point, coord img_size, std::complex<double> top_left, std::complex<double> bottom_right)
{
    std::complex<double> result;
    result.real(lerp(top_left.real(), bottom_right.real(), (double)point.first / img_size.first));
    result.imag(lerp(top_left.imag(), bottom_right.imag(), (double)point.second / img_size.second));

    return result;
}

//returns 0 if c is in the set, otherwise the return value can be used for color
unsigned char mandelbrot_iter(std::complex<double> c, unsigned int max_iter)
{
    std::complex<double> z = c;
    unsigned char result = 0;

    for(unsigned int i = 1; i <= max_iter; i++)
    {
        if(std::abs(z) > 2)
        {
            result = 1 + i * 254 / max_iter;
            break;
        }

        z = z * z + c;
    }

    return result;
}


void pgm_write_hdr(std::ofstream& fs, coord img_size)
{
    std::string hdr = "P5 ";
    hdr += std::to_string(img_size.first);
    hdr += " ";
    hdr += std::to_string(img_size.second);
    hdr += " 255\n";

    fs.write(hdr.c_str(), hdr.length());
}
