#include <cstddef>

using std::size_t;

class Array {
public:
	Array();
//    ~Array();
//    Array(const Array& other);
//    Array& operator=(const Array& other);

	Array operator+(const Array& other) const;

	int at(size_t index) const;
	size_t size() const;
	void push(int value);

private:
	int* data;

	// We don't want this to collide with size(), which gets the value publicly.
	size_t _size;
};
