#include "EnemyBullet.h"


void EnemyBullet::Initialize() {
    pos = { 0.0f, 0.0f };
    radius = 5.0f;
    velocity = { 0.0f, 10.0f };
    isShot = false;
}



EnemyBullet::EnemyBullet() {
    pos = { 0.0f, 0.0f };
    radius = 5.0f;
    velocity = { 0.0f, 10.0f };
    isShot = false;
    enemyBullet_Texture_ = Novice::LoadTexture("Resource/Enemy_Bullet/Enemy_Bullet.png");

}

void EnemyBullet::Shoot(const Vector2& startPos) {
    pos = startPos;
    isShot = true;
}

void EnemyBullet::Update() {
    if (!isShot) return;

    pos.x += velocity.x;
    pos.y += velocity.y;

    // 画面外に出たら消す
    if (pos.y - radius > 720) {
        isShot = false;
    }
}

void EnemyBullet::Draw()  {
    if (!isShot) return;
    
    Novice::DrawSprite(
        static_cast<int>(pos.x - radius),
        static_cast<int>(pos.y - radius),
        enemyBullet_Texture_,
        1.0f, 1.0f, 0.0f, WHITE);
}
