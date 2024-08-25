//
// Created by white on 2024-08-23.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "Scene.h"


class MenuScene : public Scene {
public:
    MenuScene(GameEngine* game) : Scene(game) {}
    void start() override;
    void update() override;
    void render() override;
    void doAction(const Action& action) override;
    void onEnd() override;
};



#endif //MENUSCENE_H
