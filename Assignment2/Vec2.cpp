#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin):x(xin), y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return ( (x ==rhs.x) && (y == rhs.y));
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return ((x != rhs.x) || (y != rhs.y));
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x+rhs.x, y+rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
	return Vec2(x*val, y*val);
}

Vec2 Vec2::operator/(const float val) const
{
	return Vec2(x/val, y/val);
}

Vec2 Vec2::operator+=(const Vec2& rhs)
{
	return Vec2(x += rhs.x, y += rhs.y);
}

Vec2 Vec2::operator-=(const Vec2& rhs)
{
	return Vec2(x -= rhs.x, y -= rhs.y);
}

Vec2 Vec2::operator*=(const float val)
{
	return Vec2(x*=val, y*=val);
}

Vec2 Vec2::operator/=(const float val)
{
	return Vec2(x /= val, y /= val);
}

float Vec2::dist(const Vec2& rhs) const
{
	return sqrtf((rhs.x-x)* (rhs.x - x) + (rhs.y-y)* (rhs.y - y));
}

void Vec2::normalize()
{
	*this /= this->length();
}

float Vec2::length() const
{
	return sqrtf(x*x+y*y);
}
