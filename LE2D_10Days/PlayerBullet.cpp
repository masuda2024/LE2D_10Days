#include "PlayerBullet.h"
#include <Novice.h>



void PlayerBullet::Initialize() {
    isShot = false;
    pos = { 0, 0 };
    velocity = { 0, -10 };
    radius = 5;
}



PlayerBullet::PlayerBullet() {
    isShot = false;
    pos = { 0, 0 };
    velocity = { 0, -10 };
    radius = 5;
    playerBullet_Texture_ = Novice::LoadTexture("Resource/Player_Bullet/Player_Bullet.png");

}



void PlayerBullet::Shoot(const Vector2& startPos) {
    if (!isShot) {
        isShot = true;
        pos = startPos;
    }
}

void PlayerBullet::Update() {
    if (isShot) {
        pos.x += velocity.x;
        pos.y += velocity.y;
        if (pos.y < 0) isShot = false;
    }
}

void PlayerBullet::Draw()  {
    if (isShot) {
        /*
        Novice::DrawBox((int)(pos.x - radius), (int)(pos.y - radius),
            (int)(radius * 2), (int)(radius * 2),0.0f,
            BLUE, kFillModeSolid);*/
        Novice::DrawSprite(
            static_cast<int>(pos.x - radius),
            static_cast<int>(pos.y - radius),
            playerBullet_Texture_,
            1.0f, 1.0f, 0.0f, WHITE);
    }
}
