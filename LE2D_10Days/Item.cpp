#include "Item.h"
#include <ctime> // time()
#include "time.h"
#include <Novice.h>






void Item::Initialize() {
    const int WL = 0;
    const int WR = 1280;
    const int WT = 0;
    const int WB = 720;
    //�����������_������������

    unsigned int currentTime = static_cast<int>(time(nullptr));
    srand(currentTime);

    //�_�u���A�^�b�N
    float PosXA = static_cast<float>(rand() % WR);
    float PosYA = static_cast<float>(rand() % -10);

    //�ǔ��e
    //float PosXB = static_cast<float>(rand() % WR);
    //float PosYB = static_cast<float>(rand() % -10);
   
    pos = { PosXA, PosYA };
    radius = 20.0f;
    speed = { 0.0f, 1.0f };
    isAppear = true;
    isGet = false;
    dodgeCooldown = 0;
    dodgeDuration = 0;
    isDodging = false;
	isAlive = true;
	itemTexture1_ = Novice::LoadTexture("Resource/Items/doubleAttack.png");
}


void Item::Move(int windowLeft, int windowRight, const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount) {
	if (dodgeCooldown > 0) {
		dodgeCooldown--;
	}
	if (dodgeDuration > 0) {
		dodgeDuration--;
		if (dodgeDuration == 0) {
			isDodging = false;
			dodgeCooldown = 60; //�N�[���^�C��
		}
	}

	// �e���߂����`�F�b�N
	if (!isDodging && dodgeCooldown <= 0) {
		float nearestDistance = 9999.9f;
		Vector2 nearestBulletPos{};
		bool foundBullet = false;

		for (int i = 0; i < bulletCount; i++) {
			if (!bullets[i].IsShot()) continue;

			float dx = bullets[i].GetPos().x - pos.x;
			float dy = bullets[i].GetPos().y - pos.y;
			float dist = dx * dx + dy * dy;

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestBulletPos = bullets[i].GetPos();
				foundBullet = true;
			}
		}

		if (foundBullet && nearestDistance < 200 * 200) { //������N����ԍ���
			isDodging = true;
			dodgeDuration = 20; // 20f�������

			if (nearestBulletPos.x > pos.x) {
				pos.x -= speed.x * 8;
			} else {
				pos.x += speed.x * 8;
			}
		}
	}
	
	//��ʊO�ɏo�Ȃ��悤�ɂ���
	if (pos.x - radius < windowLeft) pos.x = windowLeft + radius;
	if (pos.x + radius > windowRight) pos.x = windowRight - radius;
}






void Item::Draw() {
	if (isAlive) {
		
		Novice::DrawSprite(
			static_cast<int>(pos.x - radius),
			static_cast<int>(pos.y - radius),
			itemTexture1_,
			1.0f, 1.0f, 0.0f, WHITE);
	} 
}




void Item::Update()
{
	if (isHit) {
		hitTimer--;
		if (hitTimer <= 0.0f) {
			isHit = false;
		}
	}

}

void Item::Hit()
{
	isHit = true;
	hitTimer = hitDuration;
}

bool Item::CheckHit(const Vector2& bulletPos, float bulletRadius) {
	if (!isHit) {
		float dx = bulletPos.x - pos.x;
		float dy = bulletPos.y - pos.y;
		float distSq = dx * dx + dy * dy;
		float hitRange = radius + bulletRadius;

		if (distSq < hitRange * hitRange) {
			isHit = true;
			hitTimer = 60; // 60f ��e���
			return true;
		}
	}

	return false;
}

