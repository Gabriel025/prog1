#include <stdio.h>
#include <math.h>

void damp_matrix(int n, double mat[n][n], double d);
void print_array(int n, double array[n]);
double delta(int n, double vec[n], double prev_vec[n]);

int main(void)
{
    /*
        The columns of M represent the pages in terms
        of links from other sites that point to them.
        (The elements of each column add up to 1.)
    */
    double M[4][4] = {
        {0.0, 0.0, 0.33, 0.0},
        {1.0, 0.5, 0.33, 1.0},
        {0.0, 0.5, 0.00, 0.0},
        {0.0, 0.0, 0.33, 0.0}
    };

    //Apply the usual damping factor to M (this way the iterations themselves are simpler)
    damp_matrix(4, M, 0.85);

    double PR[4] = {1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0};
    double PR_prev[4] = {0.0, 0.0, 0.0, 0.0};

    int i = 0, j = 0;

    for (;;)
    {
        printf("Avg: %f", delta(4, PR, PR_prev));
        if (delta(4, PR, PR_prev) < 0.00001)
            break;

        //PageRank iteration:
        Amulx(4, M, PR, PR_prev);
    }
    kiir(4, PR);
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
    int i[n][4];
}

double delta(int n, double vec[n], double prev_vec[n])
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += (vec[i] - prev_vec[i]) * (vec[i] - prev_vec[i]);
    
    return sqrt(sum);
}

void print_array(int n, double array[n])
{
    for (int i = 0; i < n; i++)
        printf("%f\n", array[i]);
}

//A good paper explaining PR: http://home.ie.cuhk.edu.hk/~wkshum/papers/pagerank.pdf
//(Slightly different approach: https://www.cs.princeton.edu/~chazelle/courses/BIB/pagerank.htm)