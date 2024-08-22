//
// Created by white on 2024-08-18.
//

#ifndef VEC2_H
#define VEC2_H



class Vec2 {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float other) const;
    Vec2 operator/(float other) const;

    void operator+=(const Vec2& other);
    void operator-=(const Vec2& other);
    void operator*=(float other);
    void operator/=(float other);

    float magnitude() const;
    float distance(const Vec2& other) const;
    Vec2 normalize() const;
};



#endif //VEC2_H
