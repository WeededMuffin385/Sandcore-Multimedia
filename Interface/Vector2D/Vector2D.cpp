import Sandcore.Vector2D;


template class Vector2D<int>;
template class Vector2D<double>;

template <typename type>
Vector2D<type>::Vector2D(type x, type y) : x(x), y(y) {
}

template <typename type>
bool Vector2D<type>::operator<(const Vector2D<type>& right) const {
	if (this->x < right.x) return true;
	else if (this->x > right.x) return false;

	if (this->y < right.y) return true;
	else if (this->y > right.y) return false;

	return false;
}

template <typename type>
Vector2D<type> Vector2D<type>::operator+(const Vector2D<type>& right) {
	Vector2D<type> buffer = *this;

	buffer += right;

	return buffer;
}

template <typename type>
Vector2D<type> Vector2D<type>::operator-(const Vector2D<type>& right) {
	Vector2D<type> buffer = *this;

	buffer -= right;

	return buffer;
}

template <typename type>
Vector2D<type> Vector2D<type>::operator*(const int right) {
	Vector2D<type> buffer = *this;

	buffer.x *= right;
	buffer.y *= right;

	return buffer;
}

template <typename type>
void Vector2D<type>::operator+=(const Vector2D<type>& right) {
	this->x += right.x;
	this->y += right.y;
}

template <typename type>
void Vector2D<type>::operator-=(const Vector2D<type>& right) {
	this->x -= right.x;
	this->y -= right.y;
}

template <typename type>
bool Vector2D<type>::operator==(const Vector2D<type>& right) const {
	return x == right.x && y == right.y;
}

template <typename type>
Vector2D<type>::operator Vector2D<int>() const {
	return Vector2D<int>(x, y);
}

template <typename type>
Vector2D<type>::operator Vector2D<double>() const {
	return Vector2D<double>(x, y);
}