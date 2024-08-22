//
// Created by white on 2024-08-18.
//

#ifndef SHAPEPROPERTIES_H
#define SHAPEPROPERTIES_H

#include <string>

enum class ShapeType {
    CIRCLE,
    RECTANGLE,
    TRIANGLE
};

class ShapeProperties {
public:
    virtual ~ShapeProperties() = default;

    ShapeType type = ShapeType::CIRCLE;
    std::string name = "Shape";
    float initPosX = 0.0f;
    float initPosY = 0.0f;
    float speedX = 0.0f;
    float speedY = 0.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};
    float scale = 1.0f;
    bool isDrawn = false;

    ShapeProperties() = default;
    ShapeProperties(ShapeType type, const std::string& name, bool isDrawn, float scale, float speedX, float speedY, const float* color)
        : type(type), name(name), isDrawn(isDrawn), scale(scale), speedX(speedX), speedY(speedY), color{color[0], color[1], color[2]} {}

    virtual float get_boundary() const {
        return 0.0f;
    }
};

class CircleProperties : public ShapeProperties {
public:
    float radius = 50.0f;
    int segments = 32;
    float get_boundary() const override{
        return radius;
    }
};

class RectangleProperties : public ShapeProperties {
public:
    float width = 100.0f;
    float height = 50.0f;
    float get_boundary() const override{
        return std::max(width / 2, height / 2);
    }
};

#endif //SHAPEPROPERTIES_H
