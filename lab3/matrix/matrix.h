#include <initializer_list>
#include <ostream>

class Matrix {
public:
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<int>> initializer_list);
	Matrix(const Matrix& other);
	~Matrix();
	Matrix& operator=(const Matrix& other);
	Matrix operator+(const Matrix& other) const;
	bool operator==(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
	int** data;
	size_t rows;
	size_t columns;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
