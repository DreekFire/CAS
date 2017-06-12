#pragma once
#include <iostream>
#include "matrix.h"
#include <string.h>

class matrix {
private:
    double *array;

    //remember that matrices are column-major indexed
    int m_X;
    int m_Y;
public:
    matrix(int w, int h);
    ~matrix();

    int getX() const;
    int getY() const;
    double get(int x, int y) const;
    void set(int x, int y, double a);

    matrix add(matrix m);
    matrix subtract(matrix m);
    matrix dot(matrix m);
    matrix cross(matrix m);
    matrix mul_scalar(double scalar);
    matrix divide_e(matrix m);
    matrix transpose();
    matrix inverse();
    double determinant();
};