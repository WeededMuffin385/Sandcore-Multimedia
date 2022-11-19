export module Sandcore.Vector2D;

export template <typename type>
class Vector2D {
public:
	Vector2D(type x = 0, type y = 0);

	bool operator<(const Vector2D<type>& right) const;

	Vector2D<type> operator+(const Vector2D<type>& right);
	Vector2D<type> operator-(const Vector2D<type>& right);

	Vector2D<type> operator*(const int right);

	void operator+=(const Vector2D<type>& right);
	void operator-=(const Vector2D<type>& right);
	bool operator==(const Vector2D<type>& right) const;

	operator Vector2D<int>() const;
	operator Vector2D<double>() const;

public:
	type x;
	type y;
};