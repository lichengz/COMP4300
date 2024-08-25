//
// Created by white on 2024-08-23.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <iostream>

#include "GameSceneSettings.h"
#include "Player.h"
#include "Scene.h"


class GameScene : public Scene {
    GameSceneSettings m_gameSceneSettings;
    std::shared_ptr<Player> m_player;
public:
    GameScene(GameEngine* game) : Scene(game) {}
    void start() override;
    void update() override;
    void render() override;
    void doAction(const Action& action) override;
    void onEnd() override;

    void initPlayer();
    void sMovement();
    void sAnimation();

    Vec2 getScreenPosFromGridPos(Vec2 gridPos, const std::shared_ptr<Entity> &entity);
};



#endif //GAMESCENE_H
