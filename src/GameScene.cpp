//
// Created by white on 2024-08-23.
//

#include "GameScene.h"

#include "GameEngine.h"
#include "Player.h"

void GameScene::start() {
    initPlayer();
    m_actionMap = {
        {sf::Keyboard::Key::A,ActionType::MOVE_LEFT},
        {sf::Keyboard::Key::D,ActionType::MOVE_RIGHT},
        {sf::Keyboard::Key::Space,ActionType::JUMP}
    };
}

void GameScene::update() {
    sMovement();
    sAnimation();
}

void GameScene::render() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->cAnimation) {
            if (!entity->cAnimation->getSprite().getTexture()) {
                std::cerr << "Sprite has no texture!" << std::endl;
            }
            m_game->getWindow().draw(entity->cAnimation->getSprite());
        }
    }
}

void GameScene::doAction(const Action &action) {
    switch (action.getState()) {
        case ActionState::START:
            switch (action.getType()) {
                case ActionType::MOVE_LEFT:
                    m_player->moveLeft();
                break;
                case ActionType::MOVE_RIGHT:
                    m_player->moveRight();
                break;
                case ActionType::JUMP:
                    m_player->jump();
                break;
                default:
                    break;
            }
            break;
        case ActionState::END:
            switch (action.getType()) {
                case ActionType::MOVE_LEFT:
                case ActionType::MOVE_RIGHT:
                    m_player->stop();
                break;
                case ActionType::JUMP:
                break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void GameScene::onEnd() {
}

void GameScene::initPlayer() {
    m_player = std::make_shared<Player>(m_entityManager.addEntity("player"));

    m_player->addAnimation(PlayerState::IDLE, std::make_shared<Animation>("idle", m_gameSceneSettings.idleAnimPath, m_gameSceneSettings.idleAnimFrameCount, m_gameSceneSettings.idleAnimFrameDuration, m_gameSceneSettings.idleAnimFrameSize, m_player->getEntity()->cTransform));
    m_player->addAnimation(PlayerState::RUN, std::make_shared<Animation>("run", m_gameSceneSettings.runAnimPath, m_gameSceneSettings.runAnimFrameCount, m_gameSceneSettings.runAnimFrameDuration, m_gameSceneSettings.runAnimFrameSize, m_player->getEntity()->cTransform));
    m_player->addAnimation(PlayerState::JUMP, std::make_shared<Animation>("jump", m_gameSceneSettings.jumpAnimPath, m_gameSceneSettings.jumpAnimFrameCount, m_gameSceneSettings.jumpAnimFrameDuration, m_gameSceneSettings.jumpAnimFrameSize, m_player->getEntity()->cTransform));
    m_player->setState(PlayerState::IDLE);

    m_player->setPos(getScreenPosFromGridPos(m_gameSceneSettings.playerPosition, m_player->getEntity()));
}

void GameScene::sMovement() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->cTransform && entity->cBBox) {
            if(entity->getTag() != "bullet") {
                if(entity->cTransform->position.x + entity->cTransform->velocity.x + entity->cBBox->getBBox().x > m_game->getSettings().windowWidth || entity->cTransform->position.x + entity->cTransform->velocity.x - entity->cBBox->getBBox().x < 0) {
                    entity->cTransform->velocity.x *= -1.0f;
                }
                if(entity->cTransform->position.y + entity->cTransform->velocity.y + entity->cBBox->getBBox().y > m_game->getSettings().windowHeight || entity->cTransform->position.y + entity->cTransform->velocity.y - entity->cBBox->getBBox().y < 0) {
                    entity->cTransform->velocity.y *= -1.0f;
                }
            }
            entity->cTransform->position = entity->cTransform->position + entity->cTransform->velocity;
        }
    }
}

void GameScene::sAnimation() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->cAnimation) {
            entity->cAnimation->update();
        }
    }
}

Vec2 GameScene::getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Entity> &entity) {
    float x = gridPos.x * m_gameSceneSettings.gridSize.x + entity->cAnimation->getSize().x / 2;
    float y = static_cast<float>(m_game->getSettings().windowHeight) -(gridPos.y * m_gameSceneSettings.gridSize.y + entity->cAnimation->getSize().y / 2);
    return {x, y};
}
