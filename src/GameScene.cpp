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
        {sf::Keyboard::Key::W,ActionType::JUMP}
    };
}

void GameScene::update() {
    sRigidBody();
    sMovement();
    sCollision();
    sAnimation();
}

void GameScene::render() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->hasComponent<Animation>()) {
            if (!entity->getComponent<Animation>().getSprite().getTexture()) {
                std::cerr << "Sprite has no texture!" << std::endl;
            }
            m_game->getWindow().draw(entity->getComponent<Animation>().getSprite());
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

    m_player->addAnimation(PlayerState::IDLE, std::make_shared<Animation>("idle", m_assets.m_playerIdleTexture, m_gameSceneSettings.idleAnimFrameCount, m_gameSceneSettings.idleAnimFrameDuration, m_gameSceneSettings.idleAnimFrameSize, m_player->getEntity()));
    m_player->addAnimation(PlayerState::RUN, std::make_shared<Animation>("run", m_assets.m_playerRunTexture, m_gameSceneSettings.runAnimFrameCount, m_gameSceneSettings.runAnimFrameDuration, m_gameSceneSettings.runAnimFrameSize, m_player->getEntity()));
    m_player->addAnimation(PlayerState::JUMP, std::make_shared<Animation>("jump", m_assets.m_playerJumpTexture, m_gameSceneSettings.jumpAnimFrameCount, m_gameSceneSettings.jumpAnimFrameDuration, m_gameSceneSettings.jumpAnimFrameSize, m_player->getEntity()));
    m_player->setState(PlayerState::IDLE);

    m_player->setPos(getScreenPosFromGridPos(m_gameSceneSettings.playerPosition, m_player));
}

void GameScene::loadLevel() {
    for(const auto&  tilePos: m_gameSceneSettings.tilePositions) {
        auto tile = m_entityManager.addEntity({"tile", "collider"});
        // tile->cBBox = std::make_shared<CBBox>(tile);
        // tile->cAnimation = std::make_shared<Animation>("tile", "bin/images/ground.png", 1, 0, m_gameSceneSettings.gridSize, tile);
        // tile->cTransform = std::make_shared<CTransform>(getScreenPosFromGridPos(tilePos, tile), Vec2(0, 0));
        tile->addComponent<CBBox>(tile);
        tile->addComponent<Animation>("tile", m_assets.m_tileTexture, 1, 0, m_gameSceneSettings.gridSize, tile);
        tile->addComponent<CTransform>(getScreenPosFromGridPos(tilePos, tile), Vec2(0, 0));
    }
}

void GameScene::sMovement() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->hasComponent<CTransform>() && entity->hasComponent<CBBox>()) {
            if(std::ranges::find(entity->getTags(), "bullet") == entity->getTags().end()) {
                if(entity->getComponent<CTransform>().position.x + entity->getComponent<CTransform>().velocity.x + entity->getComponent<CBBox>().getBBox().x > m_game->getSettings().windowWidth || entity->getComponent<CTransform>().position.x + entity->getComponent<CTransform>().velocity.x - entity->getComponent<CBBox>().getBBox().x < 0) {
                    // entity->getComponent<CTransform>().velocity.x *= -1.0f;
                    continue;
                }
                if(entity != m_player->getEntity() && entity->getComponent<CTransform>().position.y + entity->getComponent<CTransform>().velocity.y + entity->getComponent<CBBox>().getBBox().y > m_game->getSettings().windowHeight || entity->getComponent<CTransform>().position.y + entity->getComponent<CTransform>().velocity.y - entity->getComponent<CBBox>().getBBox().y < 0) {
                    // entity->getComponent<CTransform>().velocity.y *= -1.0f;
                    continue;
                }
            }
            entity->getComponent<CTransform>().prevPosition = entity->getComponent<CTransform>().position;
            entity->getComponent<CTransform>().position = entity->getComponent<CTransform>().position + entity->getComponent<CTransform>().velocity;
        }
    }
    if(m_player->getEntity()->getComponent<CTransform>().position.y > m_game->getSettings().windowHeight) {
        m_player->respawn();
        m_player->setPos(getScreenPosFromGridPos(m_gameSceneSettings.playerPosition, m_player));
    }
}

void GameScene::sAnimation() {
    for(const auto& entity : m_entityManager.getEntities()) {
        if(entity->hasComponent<Animation>()) {
            entity->getComponent<Animation>().update();
        }
    }
}

void GameScene::sRigidBody() {
    for(const auto& entity : m_entityManager.getEntitiesByTag("rigidbody")) {
        if(entity->hasComponent<CTransform>() && entity->hasComponent<CRigidBody>()) {
            entity->getComponent<CTransform>().velocity += {0, 0.1f};
        }
    }
}

void GameScene::sCollision() {
    m_player->isGrounded = false;
    for(const auto& rigidEntity : m_entityManager.getEntitiesByTag("rigidbody")) {
        if(rigidEntity->hasComponent<CBBox>()) {
            for(const auto& colliderEntity : m_entityManager.getEntitiesByTag("collider")) {
                if(rigidEntity != colliderEntity) {
                    if(colliderEntity->hasComponent<CBBox>()) {
                        Vec2 overlap = Utilities::getOverlap(rigidEntity->getComponent<CBBox>(), colliderEntity->getComponent<CBBox>());
                        Vec2 prevOverlap = Utilities::getPrevOverlap(rigidEntity->getComponent<CBBox>(), colliderEntity->getComponent<CBBox>());
                        if(overlap.x > 0 && overlap.y > 0) {
                            Vec2 direction = Utilities::getDirectionToCollision(rigidEntity->getComponent<CTransform>(), colliderEntity->getComponent<CTransform>());
                            float displacementX = 0;
                            if(prevOverlap.y > 0) {
                                if(direction.x < 0) {
                                    displacementX = overlap.x;
                                } else if(direction.x > 0) {
                                    displacementX = -overlap.x;
                                }
                            }
                            float displacementY = 0;
                            if(prevOverlap.x > 0) {
                                if(direction.y < 0) {
                                    displacementY = overlap.y;
                                } else if(direction.y > 0) {
                                    displacementY = -overlap.y;
                                }
                            }
                            rigidEntity->getComponent<CTransform>().position = rigidEntity->getComponent<CTransform>().position - Vec2{displacementX, displacementY};
                            rigidEntity->getComponent<CTransform>().velocity = {displacementX != 0 ? 0 : rigidEntity->getComponent<CTransform>().velocity.x, displacementY != 0 ? 0 : rigidEntity->getComponent<CTransform>().velocity.y};
                            if(rigidEntity == m_player->getEntity() && direction.y < 0) {
                                m_player->isGrounded = true;
                                if(m_player->getVel().x == 0) {
                                    m_player->setState(PlayerState::IDLE);
                                } else {
                                    m_player->setState(PlayerState::RUN);
                                }
                            }
                        }

                    }
                }
            }
        }
    }
    if(!m_player->isGrounded) {
        m_player->setState(PlayerState::JUMP);
    }
}

Vec2 GameScene::getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Entity> &entity) {
    float x = gridPos.x * m_gameSceneSettings.gridSize.x + entity->getComponent<Animation>().getSize().x / 2;
    float y = static_cast<float>(m_game->getSettings().windowHeight) -(gridPos.y * m_gameSceneSettings.gridSize.y + entity->getComponent<Animation>().getSize().y / 2);
    return {x, y};
}

Vec2 GameScene::getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Player> &player) {
    float x = gridPos.x * m_gameSceneSettings.gridSize.x + player->getMaxSpriteSize().x / 2;
    float y = static_cast<float>(m_game->getSettings().windowHeight) -(gridPos.y * m_gameSceneSettings.gridSize.y + player->getMaxSpriteSize().y / 2);
    return {x, y};
}
