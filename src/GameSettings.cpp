//
// Created by white on 2024-08-18.
//

#include "GameSettings.h"

#include <fstream>
#include <iostream>

void GameSettings::readConfigFile() {
    std::ifstream configFile("bin/config.txt");
    int r = 255;
    int g = 255;
    int b = 255;
    if(configFile.is_open()) {
        std::string word;
        while(configFile >> word) {
            if(word == "Window") {
                configFile >> windowWidth >> windowHeight;
            }else if(word == "Font") {
                configFile >> fontPath >> fontSize >> r >> g >> b;
                fontColor = sf::Color(r, g, b);
            }else if(word == "Circle") {
                auto circle = std::make_shared<CircleProperties>();
                configFile >> circle->name >> circle->initPosX >> circle->initPosY >> circle->speedX >> circle->speedY;
                configFile >> r >> g >> b;
                circle->color[0] = float(r) / 255.0f;
                circle->color[1] = float(g) / 255.0f;
                circle->color[2] = float(b) / 255.0f;
                configFile >> circle->radius;
                circle->type = ShapeType::CIRCLE;
                circle->isDrawn = true;
                shapes.push_back(circle);
            }else if(word == "Rectangle") {
                auto rectangle = std::make_shared<RectangleProperties>();
                configFile >> rectangle->name >> rectangle->initPosX >> rectangle->initPosY >> rectangle->speedX >> rectangle->speedY;
                configFile >> r >> g >> b;
                rectangle->color[0] = float(r) / 255.0f;
                rectangle->color[1] = float(g) / 255.0f;
                rectangle->color[2] = float(b) / 255.0f;
                configFile >> rectangle->width >> rectangle->height;
                rectangle->type = ShapeType::RECTANGLE;
                rectangle->isDrawn = true;
                shapes.push_back(rectangle);
            }
        }
        configFile.close();
    } else {
        std::cerr << "Error opening config file" << std::endl;
    }
}

void GameSettings::init_shapes() {
    for(const auto& shape : shapes) {
        if(shape->isDrawn) {
            switch(shape->type) {
                case ShapeType::CIRCLE: {
                    auto circle_ptr = std::static_pointer_cast<CircleProperties>(shape);
                    sf::CircleShape circle_shape(circle_ptr->radius);
                    circle_shape.setFillColor(sf::Color(circle_ptr->color[0] * 255.0f, circle_ptr->color[1] * 255.0f, circle_ptr->color[2] * 255.0f));
                    circle_shape.setPosition(circle_ptr->initPosX, circle_ptr->initPosY);
                    circle_shape.setOrigin(circle_ptr->radius, circle_ptr->radius);
                    sf_shapes_properties_map[std::make_shared<sf::CircleShape>(circle_shape)] = circle_ptr;
                    break;
                }
                case ShapeType::RECTANGLE: {
                    auto rectangle_ptr = std::static_pointer_cast<RectangleProperties>(shape);
                    sf::RectangleShape rectangle_shape(sf::Vector2f(rectangle_ptr->width, rectangle_ptr->height));
                    rectangle_shape.setFillColor(sf::Color(rectangle_ptr->color[0] * 255.0f, rectangle_ptr->color[1] * 255.0f, rectangle_ptr->color[2] * 255.0f));
                    rectangle_shape.setPosition(rectangle_ptr->initPosX, rectangle_ptr->initPosY);
                    rectangle_shape.setOrigin(rectangle_ptr->width / 2.0f, rectangle_ptr->height / 2.0f);
                    sf_shapes_properties_map[std::make_shared<sf::RectangleShape>(rectangle_shape)] = rectangle_ptr;
                    break;
                }
                default: break;
            }
        }
    }
}
