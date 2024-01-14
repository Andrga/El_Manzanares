#pragma once
template <class T>

class Vector2D
{

private:
	T x;
	T y;
public:
	Vector2D() { Vector2D(0, 0); };
	Vector2D(T a, T b) { x = a; y = b; }
	//~Vector2D() { delete& x; delete& y; } destructora no funciona
	T getX() const { return x; }
	T getY() const { return y; }

	//Sobrecargas de operadores
	Vector2D operator+(Vector2D other) const
	{
		return Vector2D(x + other.x, y + other.y);
	}
	Vector2D operator-(Vector2D other) const
	{
		return Vector2D(x - other.x, y - other.y);
	}
	T operator*(Vector2D other) const
	{
		return ((x * other.x) + (y * other.y));
	}
	Vector2D operator*(T other) const
	{
		return Vector2D(other * x, other * y);
	}
};

template <class T>
using Point2D = Vector2D<T>;