#include "vectorN.h"

template<int N> size_t Vector<N>::size() const { return scalars.size(); }

template<int N> float& Vector<N>::operator[](size_t index) { return scalars.at(index); }
template<int N> const float& Vector<N>::operator[](size_t index) const { return scalars.at(index); }

template<int N> Vector<N> Vector<N>::operator+(const Vector<N>& other) const {
	Vector<N> result;
	for (int i = 0; i < N; i++) { result[i] = scalars[i] + other[i]; }
	return result;
}
template<int N> Vector<N> Vector<N>::operator-(const Vector<N>& other) const {
	Vector<N> result;
	for (int i = 0; i < N; i++) { result[i] = scalars[i] - other[i]; }
	return result;
}
template<int N> Vector<N> Vector<N>::operator-() const {
	Vector<N> result;
	for (int i = 0; i < N; i++) { result[i] = -scalars[i]; }
	return result;
}
template<int N> Vector<N> Vector<N>::operator*(const float& scalar) const {
	Vector<N> result;
	for (int i = 0; i < N; i++) { result[i] = scalars[i]*scalar; }
	return result;
}
template<int N> Vector<N> Vector<N>::operator/(const float& scalar) const {
	if (scalar == 0) throw std::domain_error("Division by zero is not allowed.");
	Vector<N> result;
	for (int i = 0; i < N; i++) { result[i] = scalars[i]/scalar; }
	return result;
}

template<int N> Vector<N>& Vector<N>::operator=(const Vector<N>& other) {
	for (int i = 0; i < N; i++) { scalars[i] = other[i]; }
	return *this;
}

template<int N> float Vector<N>::dot(const Vector<N>& other) const {
	float result = 0;
	for (int i = 0; i < N; i++) { result += scalars[i]*other[i]; }
	return result;
}
template<int N> float Vector<N>::norm() const {
	float sum_of_squares = 0;
	for (int i = 0; i < N; i++) { sum_of_squares = scalars[i]*scalars[i]; }
	return std::sqrt(sum_of_squares);
}

template class Vector<2>;
template class Vector<3>;
template class Vector<4>;
