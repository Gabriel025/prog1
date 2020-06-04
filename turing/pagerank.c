#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>

/*
Felhasznált források:
http://home.ie.cuhk.edu.hk/~wkshum/papers/pagerank.pdf
https://www.cs.princeton.edu/~chazelle/courses/BIB/pagerank.htm (egy kissé eltérő megoldás)
*/

void damp_matrix(int n, double mat[n][n], double d);
void Amulx(int n, double A[n][n], double x[n], double result[n]);

void swap(void *a, void *b, size_t len);
double delta(int n, double vec[n], double prev_vec[n]);

void print_array(int n, double array[n]);

int main(void)
{
    /*
        M[i][j] értéke aszerint alakul, hogy
        a j sorszámú oldalon van-e az
        i sorszámú oldalra mutató link.
        M oszlopainak az összege 1
    */
    double M[4][4] = {
        {0.0, 0.0, 0.33, 0.0},
        {1.0, 0.0, 0.33, 1.0},
        {0.0, 0.5, 0.00, 0.0},
        {0.0, 0.5, 0.33, 0.0}
    };

    //"simítunk" a mátrixon (damping); ez egy egész gyakori módszer
    //a "lógó" oldalak által okozott végeten ciklusok elkerülésére
    //damp_matrix(4, M, 0.85);

    double PR[4] = {1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0};
    double PR_prev[4] = {0.0, 0.0, 0.0, 0.0};

    while(1)
    {
        if (delta(4, PR, PR_prev) < 0.000001)
            break;

        //PageRank iteration:
        Amulx(4, M, PR, PR_prev);
        swap(PR, PR_prev, sizeof(PR));
    }

    print_array(4, PR);
    return 0;
}



void damp_matrix(int size, double mat[size][size], double d)
{
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            mat[i][j] = d * mat[i][j] + (1.0 - d) / size;
}

void Amulx(int n, double A[n][n], double x[n], double result[n])
{
    for(int i = 0; i < n; i++)
    {
        result[i] = 0;
        for(int j = 0; j < n; j++)
            result[i] += A[i][j] * x[j];
    }
}

double delta(int n, double vec[n], double prev_vec[n])
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += (vec[i] - prev_vec[i]) * (vec[i] - prev_vec[i]);
    sum /= n;
    
    return sqrt(sum);
}


void swap(void *a, void *b, size_t len)
{
    char tmp;
    char *ach = (char*)a;
    char *bch = (char*)b;

    for(size_t i = 0; i < len; i++)
    {
        tmp = ach[i];
        ach[i] = bch[i];
        bch[i] = tmp;
    }
}

void print_array(int n, double array[n])
{
    for (int i = 0; i < n; i++)
        printf("%f ", array[i]);
    printf("\n");
}