#pragma once
#include "Vector2.h"
#include "PlayerBullet.h"

class Item{
public:
	//Item();
    void Initialize();
    void Move(int windowLeft, int windowRight, const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount);
    void Draw();

    void Update();
    void Hit();

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

    bool CheckHit(const Vector2& bulletPos, float bulletRadius);

    bool IsHit() const { return isHit; }

private:
    Vector2 pos;
    float radius;
    Vector2 speed;

    bool isHit = false;
    float hitTimer = 0.0f;
    float hitDuration = 30.0f;

    // クールタイム
    int dodgeCooldown;
    int dodgeDuration;
    bool isDodging;


    int isAppear;
    int isGet;
    int isAlive;
    int itemTexture1_;
};

