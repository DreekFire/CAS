#include "matrix.h"
#include <string.h>
 
matrix::matrix(int w, int h) {
	m_Y = h;
	m_X = w;
	array = new double[w*h];
}

matrix::~matrix() {
	delete[] array;
}

int matrix::getX() const {
	return m_X;
}

int matrix::getY() const {
	return m_Y;
}

double matrix::get(int x, int y) const {
	return array[(x*m_X) + y];
}

void matrix::set(int x, int y, double a) {
	array[(x*m_X) + y] = a;
}

matrix matrix::add(matrix m) {
	if (m.getX() == m_X && m.getY() == m_Y) {
		matrix res = matrix(m_Y, m_X);
		for (int id = 0; id < (m_X*m_Y); ++id) {
            res.set(id % m_X, id / m_X, get(id % m_X, id / m_X) + m.get(id % m_X, id / m_X));
        }
		return res;
	}
	std::cout << "Arrays are not same size" << std::endl;
	return m;
}

matrix matrix::subtract(matrix m) {
	if (m.getX() == m_X && m.getY() == m_Y) {
		matrix res = matrix(m_Y, m_X);
		for (int id = 0; id < (m_X*m_Y); ++id) {
            res.set(id % m_X, id / m_X, get(id % m_X, id / m_X) - m.get(id % m_X, id / m_X));
        }
		return res;
	}
	std::cout << "Arrays are not same size" << std::endl;
	return m;
}

matrix matrix::dot(matrix m) {
	if (m.getX() == m_X && m.getY() == m_Y) {
		matrix res = matrix(m_Y, m_X);
		for (int id = 0; id < (m_X*m_Y); ++id) { res.set(id % m_X, id / m_X, get(id % m_X, id / m_X) * m.get(id % m_X, id / m_X)); }
		return res;
	}
	std::cout << "Arrays are not same size" << std::endl;
	return m;
}

matrix matrix::cross(matrix m) {
	if (getX() == m.getY()) {
		matrix res = matrix(m_X, m_Y);
		double inter = 0;
		for (int i = 0; i < m_X; ++i) {
			for (int j = 0; j < m_Y; ++j) {
				for (int k = 0; k < m_Y; ++k) {
					inter += get(i, k)*m.get(k, j);
				}
				res.set(i, j, inter);
				inter = 0;
			}
		}
		return res;
	}
	std::cout << "Array dimensions are incorrect" << std::endl;
	return m;
}

matrix matrix::mul_scalar(double scalar) {
	matrix res = matrix(m_Y, m_X);
	for (int id = 0; id < (m_X*m_Y); ++id) { res.set(id % m_X, id / m_X, get(id % m_X, id / m_X) * scalar); }
	return res;
}

matrix matrix::divide_e(matrix m) {
	if (m.getX() == m_X && m.getY() == m_Y) {
		matrix res = matrix(m_Y, m_X);
		for (int id = 0; id < (m_X*m_Y); ++id) { res.set(id % m_X, id / m_X, get(id % m_X, id / m_X) / m.get(id % m_X, id / m_X)); }
		return res;
	}
	std::cout << "Arrays are not same size" << std::endl;
	return m;
}

/*matrix matrix::transpose() {

}

matrix matrix::inverse() {

}

double matrix::determinant() {
    if (m_X != m_Y) {
        if (m_X == 2) {
            return get(0, 0)*get(1, 1) - get(1, 0)*get(1, 0);
        }
        else {

        }
    }
    else {
        std::cout << "matrix is not a square matrix" << std::endl;
    }
}*/