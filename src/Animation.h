//
// Created by white on 2024-08-23.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include <iostream>
#include <memory>
#include <string>

#include "Components.h"
#include "Vec2.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


class Animation : public Transform {
    // sf::Texture m_texture;
    sf::Sprite m_sprite;
    size_t m_frameIndex = 0;
    size_t m_frameCount = 1;
    size_t m_currentFrame = 0;
    size_t m_frameDuration = 0;
    Vec2 m_frameSize = {32, 32};
    std::string m_name = "none";
    std::shared_ptr<Entity> m_entity;
public:
    Animation() = default;
    Animation(const std::string& name, const sf::Texture& m_texture, size_t frameCount, size_t frameDuration, Vec2 frameSize, const std::shared_ptr<Entity>& entity):
        m_frameCount(frameCount),
        m_frameDuration(frameDuration),
        m_frameSize(frameSize),
        m_name(name), m_entity(entity){
        // if (!m_texture.loadFromFile(texturePath)) {
        //     std::cerr << "Error loading texture!" << std::endl;
        // }
        m_sprite.setTexture(m_texture);
        m_sprite.setOrigin(m_frameSize.x / 2, m_frameSize.y / 2);
    }
    void update();
    bool hasEnded() const;
    const Vec2& getSize() const;
     sf::Sprite& getSprite();
};



#endif //ANIMATION_H
