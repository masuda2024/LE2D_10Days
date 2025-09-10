#pragma once
#include "PlayerBullet.h"
#include "Vector2.h"
#include <Novice.h>

class Item {
public:
    Item();

    void Initialize();
    void Move();
    void Draw();
    void CheckGet(PlayerBullet* bullets, int bulletCount);

    bool IsActiveGet() const { return isGet; }
    bool IsActiveAppear() const { return isAppear; }

private:
    Vector2 pos;
    float radius;
    float speedY_;
    bool isGet;
    bool isAppear;
    int respawnTimer;
    float itemCooldown;

    int graphHandleItem;
};