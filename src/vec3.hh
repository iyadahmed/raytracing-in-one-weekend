#pragma once

#include <cmath>

class Vec3
{
public:
    double x, y, z;

    Vec3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double dot(const Vec3 &other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 cross(const Vec3 &b)
    {
        Vec3 out;
        out.x = y * b.z - z * b.y;
        out.y = z * b.x - x * b.z;
        out.z = x * b.y - y * b.x;
        return out;
    }

    double length_squared() const
    {
        return x * x + y * y + z * z;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    void normalize()
    {
        *this /= length();
    }

    Vec3 normalized() const
    {
        double l = length();
        return Vec3(x / l, y / l, z / l);
    }

    Vec3 operator+(const Vec3 &other)
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3 &other)
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator-()
    {
        return Vec3(-x, -y, -z);
    }

    Vec3 operator*(const double t)
    {
        Vec3 out;
        out *= t;
        return out;
    }

    Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 &operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3 &operator/=(const double t)
    {
        return *this *= 1.0 / t;
    }
};

typedef Vec3 Point3;