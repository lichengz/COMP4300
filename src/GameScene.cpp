//
// Created by white on 2024-08-23.
//

#include "GameScene.h"

#include "GameEngine.h"
#include "Player.h"
#include "Utilities.h"

void GameScene::start() {
    initPlayer();
    loadLevel();
    m_actionMap = {
        {sf::Keyboard::Key::A,ActionType::MOVE_LEFT},
        {sf::Keyboard::Key::D,ActionType::MOVE_RIGHT},
        {sf::Keyboard::Key::Space,ActionType::JUMP}
    };
}

void GameScene::update() {
    sAnimation();
    sRigidBody();
    sMovement();
    sCollision();
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
                    std::cout << "Move left" << std::endl;
                    m_player->moveLeft();
                break;
                case ActionType::MOVE_RIGHT:
                    std::cout << "Move right" << std::endl;
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
                    std::cout << "Stop left" << std::endl;
                    m_player->stopOneDirection(Direciton::LEFT);
                break;
                case ActionType::MOVE_RIGHT:
                    std::cout << "Stop right" << std::endl;
                    m_player->stopOneDirection(Direciton::RIGHT);
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
    m_player = std::make_shared<Player>(m_entityManager.addEntity({"player", "collider", "rigidbody"}), m_gameSceneSettings);

    m_player->addAnimation(PlayerState::IDLE, std::make_shared<Animation>("idle", m_gameSceneSettings.idleAnimPath, m_gameSceneSettings.idleAnimFrameCount, m_gameSceneSettings.idleAnimFrameDuration, m_gameSceneSettings.idleAnimFrameSize, m_player->getEntity()));
    m_player->addAnimation(PlayerState::RUN, std::make_shared<Animation>("run", m_gameSceneSettings.runAnimPath, m_gameSceneSettings.runAnimFrameCount, m_gameSceneSettings.runAnimFrameDuration, m_gameSceneSettings.runAnimFrameSize, m_player->getEntity()));
    m_player->addAnimation(PlayerState::JUMP, std::make_shared<Animation>("jump", m_gameSceneSettings.jumpAnimPath, m_gameSceneSettings.jumpAnimFrameCount, m_gameSceneSettings.jumpAnimFrameDuration, m_gameSceneSettings.jumpAnimFrameSize, m_player->getEntity()));
    m_player->setState(PlayerState::IDLE);

    m_player->setPos(getScreenPosFromGridPos(m_gameSceneSettings.playerPosition, m_player));
}

void GameScene::loadLevel() {
    for(const auto&  tilePos: m_gameSceneSettings.tilePositions) {
        auto tile = m_entityManager.addEntity({"tile", "collider"});
        tile->cBBox = std::make_shared<CBBox>(tile);
        tile->cAnimation = std::make_shared<Animation>("tile", "bin/images/ground.png", 1, 0, m_gameSceneSettings.gridSize, tile);
        tile->cTransform = std::make_shared<CTransform>(getScreenPosFromGridPos(tilePos, tile), Vec2(0, 0));
    }
}

void GameScene::sMovement() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->cTransform && entity->cBBox) {
            if(std::ranges::find(entity->getTags(), "bullet") == entity->getTags().end()) {
                if(entity->cTransform->position.x + entity->cTransform->velocity.x + entity->cBBox->getBBox().x > m_game->getSettings().windowWidth || entity->cTransform->position.x + entity->cTransform->velocity.x - entity->cBBox->getBBox().x < 0) {
                    // entity->cTransform->velocity.x *= -1.0f;
                    continue;
                }
                if(entity != m_player->getEntity() && entity->cTransform->position.y + entity->cTransform->velocity.y + entity->cBBox->getBBox().y > m_game->getSettings().windowHeight || entity->cTransform->position.y + entity->cTransform->velocity.y - entity->cBBox->getBBox().y < 0) {
                    // entity->cTransform->velocity.y *= -1.0f;
                    continue;
                }
            }
            entity->cTransform->prevPosition = entity->cTransform->position;
            entity->cTransform->position = entity->cTransform->position + entity->cTransform->velocity;
        }
    }
    if(m_player->getEntity()->cTransform->position.y > m_game->getSettings().windowHeight) {
        m_player->respawn();
        m_player->setPos(getScreenPosFromGridPos(m_gameSceneSettings.playerPosition, m_player));
    }
}

void GameScene::sAnimation() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->cAnimation) {
            entity->cAnimation->update();
        }
    }
}

void GameScene::sRigidBody() {
    for(const auto& entity : m_entityManager.getEntitiesByTag("rigidbody")) {
        if(entity->cTransform && entity->cRigidBody) {
            entity->cTransform->velocity += {0, 0.1f};
        }
    }
}

void GameScene::sCollision() {
    m_player->isGrounded = false;
    for(const auto& rigidEntity : m_entityManager.getEntitiesByTag("rigidbody")) {
        if(rigidEntity->cBBox) {
            for(const auto& colliderEntity : m_entityManager.getEntitiesByTag("collider")) {
                if(rigidEntity != colliderEntity) {
                    if(colliderEntity->cBBox) {
                        Vec2 overlap = Utilities::getOverlap(rigidEntity->cBBox, colliderEntity->cBBox);
                        if(overlap.x > 0 && overlap.y > 0) {
                            rigidEntity->cTransform->position = rigidEntity->cTransform->position - Vec2{0, overlap.y};
                            rigidEntity->cTransform->velocity = {rigidEntity->cTransform->velocity.x, 0};
                            if(rigidEntity == m_player->getEntity()) {
                                m_player->isGrounded = true;
                            }
                        }

                    }
                }
            }
        }
    }
}

Vec2 GameScene::getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Entity> &entity) {
    float x = gridPos.x * m_gameSceneSettings.gridSize.x + entity->cAnimation->getSize().x / 2;
    float y = static_cast<float>(m_game->getSettings().windowHeight) -(gridPos.y * m_gameSceneSettings.gridSize.y + entity->cAnimation->getSize().y / 2);
    return {x, y};
}

Vec2 GameScene::getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Player> &player) {
    float x = gridPos.x * m_gameSceneSettings.gridSize.x + player->getMaxSpriteSize().x / 2;
    float y = static_cast<float>(m_game->getSettings().windowHeight) -(gridPos.y * m_gameSceneSettings.gridSize.y + player->getMaxSpriteSize().y / 2);
    return {x, y};
}
