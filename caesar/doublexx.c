#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Alsó háromszögmátrix (lower triangular matrix) struktúra
typedef struct {int size; double** data;} l_tri_mat;

l_tri_mat ltm_create_matrix(int size);
void ltm_delete_matrix(l_tri_mat* matrix);

double ltm_get_value(l_tri_mat matrix, int row, int col);
int ltm_set_value(l_tri_mat matrix, int row, int col, double value);

void ltm_print_matrix(l_tri_mat matrix, int precision);


double randd(double min, double max);





int main()
{
    srand(42); //Csak azért, hogy legyen mivel feltöltenünk a mátrixot

    l_tri_mat mat = ltm_create_matrix(16);

    for(int i = 0; i < mat.size; i++)
        for(int j = 0; j < mat.size; j++) //Próbaként írjunk a mátrix felső részébe is (nem lesz tárolva)
            ltm_set_value(mat, i, j, randd(-10, 10));

    ltm_print_matrix(mat, 2);

    printf("mat.data:\t0x%lX\nmat.data[0]:\t0x%lX\n*mat.data[0]:\t%lf\n", mat.data, mat.data[0], *mat.data[0]);

    ltm_delete_matrix(&mat);

    return 0;
}


//Lefoglal egy size méretű háromszögmátrixot
l_tri_mat ltm_create_matrix(int size)
{
    l_tri_mat result;
    result.size = size;

    result.data = malloc(sizeof(double*) * size);

    for(int i = 0; i < size; i++)
        result.data[i] = calloc(i + 1, sizeof(double));

    return result;
}

//Törli a megadott a.h. mátrixot, és felszabadítja az annak lefoglalt helyet
void ltm_delete_matrix(l_tri_mat* matrix)
{
    for(int i = 0; i < matrix->size; i++) free(matrix->data[i]);

    free(matrix->data);
    matrix->data = matrix->size = 0;
}

//Visszaadja a mátrix row-adik sorában és col-adik oszlopában szereplő értéket (vagy 0-át ha nem a határokon kívül vagyunk)
double ltm_get_value(l_tri_mat matrix, int row, int col)
{
    if(row < 0 || col < 0 || row >= matrix.size || col > row) return 0.0;

    return matrix.data[row][col]; 
}

//Beállítja a megfelelő helyen lévő értéket a mátrixban (ha row és col határokon kívül vannak, 0-ával tér vissza)
int ltm_set_value(l_tri_mat matrix, int row, int col, double value)
{
    if(row < 0 || col < 0 || row >= matrix.size || col > row) return 0;

    matrix.data[row][col] = value;
    return 1;
}

//Alsó háromszögmátrix kiírása
void ltm_print_matrix(l_tri_mat matrix, int precision)
{
    for(int i = 0; i < matrix.size; i++)
    {
        for(int j = 0; j < matrix.size; j++)
            printf("% .*f\t", precision, ltm_get_value(matrix, i, j));
        
        printf("\n");
    }
}


//Random double érték min és max között
double randd(double min, double max)
{
    return min + (double)rand() / RAND_MAX * (max - min);
}