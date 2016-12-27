#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <exception>

using namespace std;

struct position
{
    int x;
    int y;
};

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

void populate_matrix(double** matrix, int size)
{
    number_variables(matrix[0], size);
    srand(time(NULL));
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 20 + 1;
            if (rand() % 2 == 0)
                matrix[i][j] *= -1;
        }
    }
}

void calculate_row(double* row_to_change, double* row_to_add, int size, double multipler)
{
    for (int i = 0; i < size - 1; i++)
    {
        row_to_change[i] += (row_to_add[i] * multipler);
        if (abs(row_to_change[i]) < pow(10,-4))
            row_to_change[i] = 0;
    }
}

void zero_under(double** matrix, int size, int x, int y)
{ 
    for (int i = 1; x + i < size; i++)
    {
        double multipler =  -1 * matrix[x + i][y] / matrix[x][y];
        calculate_row(matrix[x + i], matrix[x], size, multipler);
        print_matrix(matrix, size);
    }
}

swap(double** matrix, int x1, int y1, int x2, int y2)
{
    double tmp = matrix[x1][y1];
    matrix[x1][y1] = matrix[x2][y2];
    matrix[x2][y2] = tmp;
}

swap_row(double** matrix, int size, int idx1, int idx2)
{
    double* row1 = matrix[idx1];
    double* row2 = matrix[idx2];
    for(int i = 0; i < size; i++)
    {
        swap(matrix, idx1, i, idx2, i);
    }
}

swap_column(double** matrix, int size, int idx1, int idx2)
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
            if (matrix[i][j] > max)
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



int main()
{
    cout << setprecision(3);
    int size = 100;
    double** matrix = create_matrix(size);
    populate_matrix(matrix, size);
    print_matrix(matrix, size);
    gauss_eliminate(matrix, size);
}