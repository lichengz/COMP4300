//
// Created by white on 2024-08-23.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <iostream>

#include "Assets.h"
#include "GameSceneSettings.h"
#include "Player.h"
#include "Scene.h"


class GameScene : public Scene {
    GameSceneSettings m_gameSceneSettings;
    std::shared_ptr<Player> m_player;
    Assets m_assets;
public:
    GameScene(GameEngine* game) : Scene(game) {}
    void start() override;
    void update() override;
    void render() override;
    void doAction(const Action& action) override;
    void onEnd() override;

    void initPlayer();
    void loadLevel();
    void sMovement();
    void sAnimation();
    void sRigidBody();
    void sCollision();

    Vec2 getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Entity> &entity);
    Vec2 getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Player> &player);
};



#endif //GAMESCENE_H
