//
// Created by white on 2024-08-18.
//

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include "ShapeProperties.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>

class GameSettings {
public:
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string fontPath = "fonts/Arial.ttf";
    int fontSize = 24;
    float playerRadius = 20.0f;
    int playerSegments = 8;
    float playerOutlineThickness = 3.0f;
    float playerSpeed = 5.0f;
    float enemySpeed = 2.0f;
    float bulletSpeed = 10.0f;
    int enemySpawnInterval = 60;
    float enemyMinRadius = 10.0f;
    float enemyMaxRadius = 50.0f;
    int enemyMinSegments = 3;
    int enemyMaxSegments = 20;
    sf::Color fontColor = sf::Color::White;
    std::vector<std::shared_ptr<ShapeProperties>> shapes;
    std::map<std::shared_ptr<sf::Shape>, std::shared_ptr<ShapeProperties>> sf_shapes_properties_map;
    void readConfigFile();
    void init_shapes();
};
#endif //GAMESETTINGS_H
