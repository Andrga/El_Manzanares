#pragma once
template <class T>

class Vector2D
{

private:
	T x;
	T y;
public:
	Vector2D() = default;
	Vector2D(T a, T b) { x = a; y = b; }
	T getX() { return x; }
	T getY() { return y; }
	Vector2D operator+(Vector2D other)
	{
		return Vector2D(x + other.x, y + other.y);
	}
	Vector2D operator-(Vector2D other)
	{
		return Vector2D(x - other.x, y - other.y)
	}
	T operator*(Vector2D other)
	{
		return ((x * other.x) + (y * other.y))
	}
	Vector2D operator*(T other)
	{
		return Vector2D(other * x, other * y)
	}
};

template <class T>
using Point2D = Vector2D<T>;