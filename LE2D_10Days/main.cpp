#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Line.h"
#include "Vector2.h"
#include <cstring>

const char kWindowTitle[] = "2061_線押し陣取り";

const int WL = 0;
const int WR = 1280;
const int WT = 0;
const int WB = 720;

enum Scene {
    TITLE,
    CREDIT,
    TUTORIAL1,
    TUTORIAL2,
    GAME,
    CLEAR,
    OVER
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Novice::Initialize(kWindowTitle, WR, WB);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };



#pragma region 初期化
    int scene = TITLE;

    Player player;
    Enemy enemy;
    Line line;

    const int kMaxPlayerBullets = 8;
    PlayerBullet playerBullets[kMaxPlayerBullets];

    const int kMaxEnemyBullets = 8;
    EnemyBullet enemyBullets[kMaxEnemyBullets];

    int playerBulletCooldown = 0;
    int enemyBulletCooldown = 0;

    int isGameOver = false;
    int isGameClear = false;
#pragma endregion

#pragma region テクスチャ

    int TitleBack = Novice::LoadTexture("Resource/Title/TitleBack.png");
    int Title1 = Novice::LoadTexture("Resource/Title/TitleFont1.png");
    int Title2 = Novice::LoadTexture("Resource/Title/TitleFont2.png");
    int Title3 = Novice::LoadTexture("Resource/Title/WarningColor.png");
    int TitleUI = Novice::LoadTexture("Resource/Title/TitleUI.png");



    int Tutorial1= Novice::LoadTexture("Resource/Tutorial/Tutorial1.png");
    int PlayerTex = Novice::LoadTexture("Resource/Player/Tank.png");

    int Clear= Novice::LoadTexture("Resource/Scene/Clear.png");
    int Over = Novice::LoadTexture("Resource/Scene/Over.png");

    int Ground= Novice::LoadTexture("Resource/Scene/Ground.png");

#pragma endregion

    while (Novice::ProcessMessage() == 0)
    {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        switch (scene) {
        case TITLE:
           


            isGameClear = false;
            isGameOver = false;
            
            
            
            Novice::DrawSprite(
                0, 0, TitleBack,
                1.0f, 1.0f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                100, 100, Title1,
                1.5f, 1.5f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                800, 400, Title2,
                1.5f, 1.5f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                0, 350, Title3,
                1.0f, 1.0f, 0.0f,
                WHITE
            );


            Novice::DrawSprite(
                354, 500, TitleUI,
                2.0f, 2.0f, 0.0f,
                WHITE
            );




            if (keys[DIK_SPACE]) {
                scene = GAME;
                break;
            }
            if (preKeys[DIK_C]) {
                scene = CREDIT;
                break;
            }
            if (preKeys[DIK_T]) {
                scene = TUTORIAL1;
                break;
            }
            break;


        case CREDIT:
            
            if (preKeys[DIK_E]) {
                scene = TITLE;
                break;
            }
            break;


        case TUTORIAL1:
            Novice::DrawSprite(
                0, 0, Tutorial1,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            Novice::DrawSprite(
                225,410, PlayerTex,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            
            
            
            
            if (preKeys[DIK_E]) {
                scene = TITLE;
                break;
            }

            if (preKeys[DIK_D]) {
                scene = TUTORIAL2;
                break;
            }


            break;

        case TUTORIAL2:
            
            if (preKeys[DIK_A]) {
                scene = TUTORIAL1;
                break;
            }
            break;

        case GAME:

            Novice::DrawSprite(
                0, 0,
                Ground,
                1.0f, 1.0f, 0.0f,
                WHITE
            );


            


            if (preKeys[DIK_C]) {
                scene = CLEAR;
                break;
            }
            if (preKeys[DIK_B]) {
                scene = OVER;
                break;
            }



        // プレイヤー移動
        player.Move(WL, WR, WT, WB, keys);

        // 敵移動
        enemy.Move(WL, WR, player.GetPos(), playerBullets, kMaxPlayerBullets);

        // プレイヤー弾発射
        if (playerBulletCooldown > 0) playerBulletCooldown--;
        if (keys[DIK_SPACE] && playerBulletCooldown <= 0){
            for (int i = 0; i < kMaxPlayerBullets; i++){
                if (!playerBullets[i].IsShot()){
                    playerBullets[i].Shoot(player.GetPos());
                    playerBulletCooldown = 10;
                    break;
                }
            }
        }

        // プレイヤー弾更新
        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Update();

        // 敵弾発射
        if (enemyBulletCooldown > 0) {
            enemyBulletCooldown--;
        };

        if (enemyBulletCooldown <= 0)
        {
            for (int i = 0; i < kMaxEnemyBullets; i++)
            {
                if (!enemyBullets[i].IsShot())
                {
                    enemyBullets[i].Shoot(enemy.GetPos());
                    enemyBulletCooldown = 30; // 敵のクールタイム
                    break;
                }
            }
        }

        //敵弾
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Update();

        //被弾判定
        for (int i = 0; i < kMaxPlayerBullets; i++) {
            if (playerBullets[i].IsShot()) {
                // Enemy判定
                if (enemy.CheckHit(playerBullets[i].GetPos(), playerBullets[i].GetRadius())) {
                    playerBullets[i].SetShot(false);

                    line.LineEnemyHit();
                }
            }
        }
        for (int i = 0; i < kMaxEnemyBullets; i++) {
            if (enemyBullets[i].IsShot()) {
                // Playe判定
                if (player.CheckHit(enemyBullets[i].GetPos(), enemyBullets[i].GetRadius())) {
                    enemyBullets[i].SetShot(false);

                    line.LinePlayerHit();
                }
            }
        }

        //被弾タイマー更新 ======
        player.Update();
        enemy.Update();

        if (line.CheckHitPlayer(player)) {
            isGameOver = true;  //負け
            scene = OVER;
        }
        if (line.CheckHitEnemy(enemy)) {
            isGameClear = true; //勝利
            scene = CLEAR;
        }



        //描画
        player.Draw();
        enemy.Draw();
        line.Draw();

        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Draw();
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Draw();

        break;


        case CLEAR:
           Novice::DrawSprite(
                0, 0, 
                Clear,
                1.0f, 1.0f,0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                isGameClear = false;

                //元の位置に戻す
                player.Initialize();
                enemy.Initialize();
                line.Initialize();
                playerBullets[kMaxPlayerBullets].Initialize();
                enemyBullets[kMaxEnemyBullets].Initialize();
                
                scene = TITLE;
                break;
            }
            break;


        case OVER:
            Novice::DrawSprite(
                0, 0,
                Over,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                isGameOver = false;
                //元の位置に戻す
                player.Initialize();
                enemy.Initialize();
                line.Initialize();
                playerBullets[kMaxPlayerBullets].Initialize();
                enemyBullets[kMaxEnemyBullets].Initialize();

                scene = TITLE;
                break;
            }
            break;
        }



        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
    }

    Novice::Finalize();
    return 0;
}
