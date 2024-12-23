#include <array>
#include <cmath>
#include <stdexcept>

template<int N> class Vector {
private:
	std::array<float, N> scalars;

public:
	size_t size() const;

	float& operator[](size_t);
	const float& operator[](size_t) const;

	Vector<N> operator+(const Vector<N>&) const;
	Vector<N> operator-(const Vector<N>&) const;
	Vector<N> operator-() const;
	Vector<N> operator*(const float&) const;
	Vector<N> operator/(const float&) const;

	Vector<N>& operator=(const Vector<N>&);

	float dot(const Vector<N>&) const;
	float norm() const;
};
