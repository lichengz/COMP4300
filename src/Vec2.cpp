//
// Created by white on 2024-08-18.
//

#include "Vec2.h"

#include <cmath>

Vec2 Vec2::operator+(const Vec2 &other) const {
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return {x - other.x, y - other.y};
}

Vec2 Vec2::operator*(float other) const {
    return {x * other, y * other};
}

Vec2 Vec2::operator/(float other) const {
    return {x / other, y / other};
}

void Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
}

void Vec2::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
}

void Vec2::operator*=(float other) {
    x *= other;
    y *= other;
}

void Vec2::operator/=(float other) {
    x /= other;
    y /= other;
}

float Vec2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

float Vec2::distance(const Vec2 &other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Vec2 Vec2::normalize() const {
    return (*this) / magnitude();
}
