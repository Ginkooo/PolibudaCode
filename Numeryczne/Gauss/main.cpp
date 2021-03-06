#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <exception>

using namespace std;

struct position
{
    int x;
    int y;
};

struct result
{
    int id;
    double value;
};

swap_results(result* result1, result* result2)
{
    result* temp = (result*)malloc(sizeof(result));
    memcpy(temp, result1, sizeof(result));
    memcpy(result1, result2, sizeof(result));
    memcpy(result2, temp, sizeof(result));
    free(temp);
}

void sort_results(result results[], int size)
{
    do
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (results[i].id > results[i+1].id)
            {
                swap_results(&results[i], &results[i + 1]);
            }
        }
        size--;
    }
    while (size > 1);
}

void print_matrix(double** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(8) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

double** create_matrix(int size)
{
    double** matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
    }

    return matrix;
}

void number_variables(double* row, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i == (size - 1))
        {
            row[i] = -1;
            break;
        }
        row[i] = i;   
    }
}

void randomize_matrix(double** matrix, int size)
{
    srand(time(NULL));
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 5;
            if (rand() % 2 == 0)
                matrix[i][j] *= -1;
        }
    }
}

void fill_matrix_from_user(double** matrix, int size)
{
    double in;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("[%d][%d] = ", i, j);
            cin >> in;
            matrix[i + 1][j] = in;
        }
    }
}

void populate_matrix(double** matrix, int size, bool do_random)
{
    number_variables(matrix[0], size);
    if (do_random)
    {  
        randomize_matrix(matrix, size);
    }
    else
    {
        fill_matrix_from_user(matrix, size);
    }
}

void calculate_row(double* row_to_change, double* row_to_add, int size, double multipler)
{
    for (int i = 0; i < size; i++)
    {
        row_to_change[i] += (row_to_add[i] * multipler);
        if (abs(row_to_change[i]) < pow(10,-10))
            row_to_change[i] = 0;
    }
}

void zero_under(double** matrix, int size, int x, int y)
{ 
    for (int i = 1; x + i < size; i++)
    {
        double multipler;
        if (matrix[x+i][y] != 0)
        {
            multipler =  -1 * matrix[x + i][y] / matrix[x][y];

            calculate_row(matrix[x + i], matrix[x], size, multipler);
        }
    }
}

void swap(double** matrix, int x1, int y1, int x2, int y2)
{
    double tmp = matrix[x1][y1];
    matrix[x1][y1] = matrix[x2][y2];
    matrix[x2][y2] = tmp;
}

void swap_row(double** matrix, int size, int idx1, int idx2)
{
    for(int i = 0; i < size; i++)
    {
        swap(matrix, idx1, i, idx2, i);
    }
}

void swap_column(double** matrix, int size, int idx1, int idx2)
{
    for (int i = 0; i < size; i++)
    {
        swap(matrix, i, idx1, i, idx2);
    }
}

position find_max(double** matrix, int size, position upper_corner)
{
    position tmp;
    tmp.x = upper_corner.x;
    tmp.y = upper_corner.y;
    double max = matrix[upper_corner.x][upper_corner.y];
    for (int i = upper_corner.x; i < size; i++)
    {
        for (int j = upper_corner.y; j < size - 1; j++)
        {
            if (fabs(matrix[i][j]) > fabs(max))
            {
                max = matrix[i][j];
                tmp.x = i;
                tmp.y = j;
            }
        }
    }
    return tmp;
}

void put_biggest(double** matrix, int size, int i, int j)
{
    position upper_corner;
    upper_corner.x = i;
    upper_corner.y = j;
    position max_pos = find_max(matrix, size, upper_corner);
    swap_row(matrix, size, upper_corner.x, max_pos.x);
    swap_column(matrix, size, upper_corner.y, max_pos.y);
}

void gauss_eliminate(double** matrix, int size)
{
    int i, j;
    for (i = 1, j = 0; i < size; i++, j++)
    {
        put_biggest(matrix, size, i, j);
        zero_under(matrix, size, i, j);
    }
}

int get_first_nz_el_idx(double* row, int size)
{
    int i = 0;
    while (i < size - 1)
    {
        if (row[i] != 0)
            return i;
        i++;
    }
    return i;
}

double sum_nz_el(double* row, int size)
{
    int first = get_first_nz_el_idx(row, size) + 1;
    int last = size - 1;
    double sum = 0;
    if (first > size - 2)
        return 0;
    while (first < last)
    {
        sum += row[first];
        first++;
    }
    return sum;
}

int get_col_last_nz_idx(double** matrix, int size, int idx)
{
    int j = size - 1;
    while (j > 0)
    {
        if (matrix[j][idx] != 0)
            return j;
        j--;
    }
}

void value_col(double** matrix, int size, int idx)
{
    int lz = get_col_last_nz_idx(matrix, size, idx);
    for (int i = 1; i < lz; i++)
    {
        matrix[i][idx] *= matrix[lz][idx];
    }
}

void mul_elements(double** matrix, int size)
{
    int l = size - 1;
    double* row;
    for (int i = size - 1; i > 0; i--)
    {
        row = matrix[i];
        int first_nz = get_first_nz_el_idx(row, size);
        row[first_nz] = ( row[l] - sum_nz_el(row, size) ) / row[first_nz];
        value_col(matrix, size, first_nz);
    }
}

result* solve_matrix(double** matrix, int size)
{
    result* results = new result[size - 1];
    gauss_eliminate(matrix, size);
    cout << "Macierz po eliminacji i wyborach elementu podstawowego:" << endl;
    print_matrix(matrix, size);
    mul_elements(matrix, size);
    for (int i = 0; i < size - 1; i++)
    {
        results[i].id = matrix[0][i];
        results[i].value = matrix[get_col_last_nz_idx(matrix, size, i)][i];
    }
    sort_results(results, size - 1);
    return results;
}

int main()
{
    cout << setprecision(5);
    cout << "Podaj szerokosc maciezy: ";
    int size;
    cin >> size;
    char in;
    cout << "Czy wygenerowac losowa macierz? (t/n):  ";
    cin >> in;
    bool randomize;
    if (in == 't' || in == 'T')
        randomize = true;
    else
        randomize = false;
    double** matrix = create_matrix(size);
    populate_matrix(matrix, size, randomize);
    print_matrix(matrix, size);
    result* results = solve_matrix(matrix, size);
    for (int i = 0; i < size - 1; i++)
    {
        cout << "x" << results[i].id << " = " << results[i].value << endl;
    }   
}