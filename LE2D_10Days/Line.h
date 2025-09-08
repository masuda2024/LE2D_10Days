﻿#pragma once
#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"

class Line {
public:
    Line();
    void Initialize();
    void Draw() ;

    void SetPos(float x, float y) { pos.x = x; pos.y = y; }
    void SetSize(float w, float h) { width = w; height = h; }

    void LinePlayerHit(); // プレイヤーに当たった時
    void LineEnemyHit();  // 敵に当たった時

    bool CheckHitPlayer(const Player& player);
    bool CheckHitEnemy(const Enemy& enemy);

private:
    Vector2 pos;
    float width;
    float height;

    int LineTexture_;

    float moveAmountPlayer; // Playerに当たったときの移動量
    float moveAmountEnemy;  // Enemyに当たったときの移動量

};
